/*
 * Copywight 2005 Nicowai Haehnwe et aw.
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Nicowai Haehnwe
 *          Jewome Gwisse
 */
#ifndef _W300_WEG_H_
#define _W300_WEG_H_

#define W300_SUWF_TIWE_MACWO (1<<16)
#define W300_SUWF_TIWE_MICWO (2<<16)
#define W300_SUWF_TIWE_BOTH (3<<16)


#define W300_MC_INIT_MISC_WAT_TIMEW	0x180
#	define W300_MC_MISC__MC_CPW_INIT_WAT_SHIFT	0
#	define W300_MC_MISC__MC_VF_INIT_WAT_SHIFT	4
#	define W300_MC_MISC__MC_DISP0W_INIT_WAT_SHIFT	8
#	define W300_MC_MISC__MC_DISP1W_INIT_WAT_SHIFT	12
#	define W300_MC_MISC__MC_FIXED_INIT_WAT_SHIFT	16
#	define W300_MC_MISC__MC_E2W_INIT_WAT_SHIFT	20
#	define W300_MC_MISC__MC_SAME_PAGE_PWIO_SHIFT	24
#	define W300_MC_MISC__MC_GWOBW_INIT_WAT_SHIFT	28

#define W300_MC_INIT_GFX_WAT_TIMEW	0x154
#	define W300_MC_MISC__MC_G3D0W_INIT_WAT_SHIFT	0
#	define W300_MC_MISC__MC_G3D1W_INIT_WAT_SHIFT	4
#	define W300_MC_MISC__MC_G3D2W_INIT_WAT_SHIFT	8
#	define W300_MC_MISC__MC_G3D3W_INIT_WAT_SHIFT	12
#	define W300_MC_MISC__MC_TX0W_INIT_WAT_SHIFT	16
#	define W300_MC_MISC__MC_TX1W_INIT_WAT_SHIFT	20
#	define W300_MC_MISC__MC_GWOBW_INIT_WAT_SHIFT	24
#	define W300_MC_MISC__MC_GWOBW_FUWW_WAT_SHIFT	28

/*
 * This fiwe contains wegistews and constants fow the W300. They have been
 * found mostwy by examining command buffews captuwed using gwxtest, as weww
 * as by extwapowating some known wegistews and constants fwom the W200.
 * I am faiwwy cewtain that they awe cowwect unwess stated othewwise
 * in comments.
 */

#define W300_SE_VPOWT_XSCAWE                0x1D98
#define W300_SE_VPOWT_XOFFSET               0x1D9C
#define W300_SE_VPOWT_YSCAWE                0x1DA0
#define W300_SE_VPOWT_YOFFSET               0x1DA4
#define W300_SE_VPOWT_ZSCAWE                0x1DA8
#define W300_SE_VPOWT_ZOFFSET               0x1DAC


/*
 * Vewtex Awway Pwocessing (VAP) Contwow
 * Stowen fwom w200 code fwom Chwistoph Bwiww (It's a guess!)
 */
#define W300_VAP_CNTW	0x2080

/* This wegistew is wwitten diwectwy and awso stawts data section
 * in many 3d CP_PACKET3's
 */
#define W300_VAP_VF_CNTW	0x2084
#	define	W300_VAP_VF_CNTW__PWIM_TYPE__SHIFT              0
#	define  W300_VAP_VF_CNTW__PWIM_NONE                     (0<<0)
#	define  W300_VAP_VF_CNTW__PWIM_POINTS                   (1<<0)
#	define  W300_VAP_VF_CNTW__PWIM_WINES                    (2<<0)
#	define  W300_VAP_VF_CNTW__PWIM_WINE_STWIP               (3<<0)
#	define  W300_VAP_VF_CNTW__PWIM_TWIANGWES                (4<<0)
#	define  W300_VAP_VF_CNTW__PWIM_TWIANGWE_FAN             (5<<0)
#	define  W300_VAP_VF_CNTW__PWIM_TWIANGWE_STWIP           (6<<0)
#	define  W300_VAP_VF_CNTW__PWIM_WINE_WOOP                (12<<0)
#	define  W300_VAP_VF_CNTW__PWIM_QUADS                    (13<<0)
#	define  W300_VAP_VF_CNTW__PWIM_QUAD_STWIP               (14<<0)
#	define  W300_VAP_VF_CNTW__PWIM_POWYGON                  (15<<0)

#	define	W300_VAP_VF_CNTW__PWIM_WAWK__SHIFT              4
	/* State based - diwect wwites to wegistews twiggew vewtex
           genewation */
#	define	W300_VAP_VF_CNTW__PWIM_WAWK_STATE_BASED         (0<<4)
#	define	W300_VAP_VF_CNTW__PWIM_WAWK_INDICES             (1<<4)
#	define	W300_VAP_VF_CNTW__PWIM_WAWK_VEWTEX_WIST         (2<<4)
#	define	W300_VAP_VF_CNTW__PWIM_WAWK_VEWTEX_EMBEDDED     (3<<4)

	/* I don't think I saw these thwee used.. */
#	define	W300_VAP_VF_CNTW__COWOW_OWDEW__SHIFT            6
#	define	W300_VAP_VF_CNTW__TCW_OUTPUT_CTW_ENA__SHIFT     9
#	define	W300_VAP_VF_CNTW__PWOG_STWEAM_ENA__SHIFT        10

	/* index size - when not set the indices awe assumed to be 16 bit */
#	define	W300_VAP_VF_CNTW__INDEX_SIZE_32bit              (1<<11)
	/* numbew of vewtices */
#	define	W300_VAP_VF_CNTW__NUM_VEWTICES__SHIFT           16

/* BEGIN: Wiwd guesses */
#define W300_VAP_OUTPUT_VTX_FMT_0           0x2090
#       define W300_VAP_OUTPUT_VTX_FMT_0__POS_PWESENT     (1<<0)
#       define W300_VAP_OUTPUT_VTX_FMT_0__COWOW_PWESENT   (1<<1)
#       define W300_VAP_OUTPUT_VTX_FMT_0__COWOW_1_PWESENT (1<<2)  /* GUESS */
#       define W300_VAP_OUTPUT_VTX_FMT_0__COWOW_2_PWESENT (1<<3)  /* GUESS */
#       define W300_VAP_OUTPUT_VTX_FMT_0__COWOW_3_PWESENT (1<<4)  /* GUESS */
#       define W300_VAP_OUTPUT_VTX_FMT_0__PT_SIZE_PWESENT (1<<16) /* GUESS */

#define W300_VAP_OUTPUT_VTX_FMT_1           0x2094
	/* each of the fowwowing is 3 bits wide, specifies numbew
	   of components */
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_0_COMP_CNT_SHIFT 0
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_1_COMP_CNT_SHIFT 3
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_2_COMP_CNT_SHIFT 6
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_3_COMP_CNT_SHIFT 9
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_4_COMP_CNT_SHIFT 12
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_5_COMP_CNT_SHIFT 15
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_6_COMP_CNT_SHIFT 18
#       define W300_VAP_OUTPUT_VTX_FMT_1__TEX_7_COMP_CNT_SHIFT 21
/* END: Wiwd guesses */

#define W300_SE_VTE_CNTW                  0x20b0
#	define     W300_VPOWT_X_SCAWE_ENA                0x00000001
#	define     W300_VPOWT_X_OFFSET_ENA               0x00000002
#	define     W300_VPOWT_Y_SCAWE_ENA                0x00000004
#	define     W300_VPOWT_Y_OFFSET_ENA               0x00000008
#	define     W300_VPOWT_Z_SCAWE_ENA                0x00000010
#	define     W300_VPOWT_Z_OFFSET_ENA               0x00000020
#	define     W300_VTX_XY_FMT                       0x00000100
#	define     W300_VTX_Z_FMT                        0x00000200
#	define     W300_VTX_W0_FMT                       0x00000400
#	define     W300_VTX_W0_NOWMAWIZE                 0x00000800
#	define     W300_VTX_ST_DENOWMAWIZED              0x00001000

/* BEGIN: Vewtex data assembwy - wots of uncewtainties */

/* gap */

#define W300_VAP_CNTW_STATUS              0x2140
#	define W300_VC_NO_SWAP                  (0 << 0)
#	define W300_VC_16BIT_SWAP               (1 << 0)
#	define W300_VC_32BIT_SWAP               (2 << 0)
#	define W300_VAP_TCW_BYPASS		(1 << 8)

/* gap */

/* Whewe do we get ouw vewtex data?
 *
 * Vewtex data eithew comes eithew fwom immediate mode wegistews ow fwom
 * vewtex awways.
 * Thewe appeaws to be no mixed mode (though we can fowce the pitch of
 * vewtex awways to 0, effectivewy weusing the same ewement ovew and ovew
 * again).
 *
 * Immediate mode is contwowwed by the INPUT_CNTW wegistews. I am not suwe
 * if these wegistews infwuence vewtex awway pwocessing.
 *
 * Vewtex awways awe contwowwed via the 3D_WOAD_VBPNTW packet3.
 *
 * In both cases, vewtex attwibutes awe then passed thwough INPUT_WOUTE.
 *
 * Beginning with INPUT_WOUTE_0_0 is a wist of WOWDs that woute vewtex data
 * into the vewtex pwocessow's input wegistews.
 * The fiwst wowd woutes the fiwst input, the second wowd the second, etc.
 * The cowwesponding input is wouted into the wegistew with the given index.
 * The wist is ended by a wowd with INPUT_WOUTE_END set.
 *
 * Awways set COMPONENTS_4 in immediate mode.
 */

#define W300_VAP_INPUT_WOUTE_0_0            0x2150
#       define W300_INPUT_WOUTE_COMPONENTS_1     (0 << 0)
#       define W300_INPUT_WOUTE_COMPONENTS_2     (1 << 0)
#       define W300_INPUT_WOUTE_COMPONENTS_3     (2 << 0)
#       define W300_INPUT_WOUTE_COMPONENTS_4     (3 << 0)
#       define W300_INPUT_WOUTE_COMPONENTS_WGBA  (4 << 0) /* GUESS */
#       define W300_VAP_INPUT_WOUTE_IDX_SHIFT    8
#       define W300_VAP_INPUT_WOUTE_IDX_MASK     (31 << 8) /* GUESS */
#       define W300_VAP_INPUT_WOUTE_END          (1 << 13)
#       define W300_INPUT_WOUTE_IMMEDIATE_MODE   (0 << 14) /* GUESS */
#       define W300_INPUT_WOUTE_FWOAT            (1 << 14) /* GUESS */
#       define W300_INPUT_WOUTE_UNSIGNED_BYTE    (2 << 14) /* GUESS */
#       define W300_INPUT_WOUTE_FWOAT_COWOW      (3 << 14) /* GUESS */
#define W300_VAP_INPUT_WOUTE_0_1            0x2154
#define W300_VAP_INPUT_WOUTE_0_2            0x2158
#define W300_VAP_INPUT_WOUTE_0_3            0x215C
#define W300_VAP_INPUT_WOUTE_0_4            0x2160
#define W300_VAP_INPUT_WOUTE_0_5            0x2164
#define W300_VAP_INPUT_WOUTE_0_6            0x2168
#define W300_VAP_INPUT_WOUTE_0_7            0x216C

/* gap */

/* Notes:
 *  - awways set up to pwoduce at weast two attwibutes:
 *    if vewtex pwogwam uses onwy position, fgwwx wiww set nowmaw, too
 *  - INPUT_CNTW_0_COWOW and INPUT_CNTW_COWOW bits awe awways equaw.
 */
#define W300_VAP_INPUT_CNTW_0               0x2180
#       define W300_INPUT_CNTW_0_COWOW           0x00000001
#define W300_VAP_INPUT_CNTW_1               0x2184
#       define W300_INPUT_CNTW_POS               0x00000001
#       define W300_INPUT_CNTW_NOWMAW            0x00000002
#       define W300_INPUT_CNTW_COWOW             0x00000004
#       define W300_INPUT_CNTW_TC0               0x00000400
#       define W300_INPUT_CNTW_TC1               0x00000800
#       define W300_INPUT_CNTW_TC2               0x00001000 /* GUESS */
#       define W300_INPUT_CNTW_TC3               0x00002000 /* GUESS */
#       define W300_INPUT_CNTW_TC4               0x00004000 /* GUESS */
#       define W300_INPUT_CNTW_TC5               0x00008000 /* GUESS */
#       define W300_INPUT_CNTW_TC6               0x00010000 /* GUESS */
#       define W300_INPUT_CNTW_TC7               0x00020000 /* GUESS */

/* gap */

/* Wowds pawawwew to INPUT_WOUTE_0; Aww wowds that awe active in INPUT_WOUTE_0
 * awe set to a swizzwing bit pattewn, othew wowds awe 0.
 *
 * In immediate mode, the pattewn is awways set to xyzw. In vewtex awway
 * mode, the swizzwing pattewn is e.g. used to set zw components in textuwe
 * coowdinates with onwy tweo components.
 */
#define W300_VAP_INPUT_WOUTE_1_0            0x21E0
#       define W300_INPUT_WOUTE_SEWECT_X    0
#       define W300_INPUT_WOUTE_SEWECT_Y    1
#       define W300_INPUT_WOUTE_SEWECT_Z    2
#       define W300_INPUT_WOUTE_SEWECT_W    3
#       define W300_INPUT_WOUTE_SEWECT_ZEWO 4
#       define W300_INPUT_WOUTE_SEWECT_ONE  5
#       define W300_INPUT_WOUTE_SEWECT_MASK 7
#       define W300_INPUT_WOUTE_X_SHIFT     0
#       define W300_INPUT_WOUTE_Y_SHIFT     3
#       define W300_INPUT_WOUTE_Z_SHIFT     6
#       define W300_INPUT_WOUTE_W_SHIFT     9
#       define W300_INPUT_WOUTE_ENABWE      (15 << 12)
#define W300_VAP_INPUT_WOUTE_1_1            0x21E4
#define W300_VAP_INPUT_WOUTE_1_2            0x21E8
#define W300_VAP_INPUT_WOUTE_1_3            0x21EC
#define W300_VAP_INPUT_WOUTE_1_4            0x21F0
#define W300_VAP_INPUT_WOUTE_1_5            0x21F4
#define W300_VAP_INPUT_WOUTE_1_6            0x21F8
#define W300_VAP_INPUT_WOUTE_1_7            0x21FC

/* END: Vewtex data assembwy */

/* gap */

/* BEGIN: Upwoad vewtex pwogwam and data */

/*
 * The pwogwammabwe vewtex shadew unit has a memowy bank of unknown size
 * that can be wwitten to in 16 byte units by wwiting the addwess into
 * UPWOAD_ADDWESS, fowwowed by data in UPWOAD_DATA (muwtipwes of 4 DWOWDs).
 *
 * Pointews into the memowy bank awe awways in muwtipwes of 16 bytes.
 *
 * The memowy bank is divided into aweas with fixed meaning.
 *
 * Stawting at addwess UPWOAD_PWOGWAM: Vewtex pwogwam instwuctions.
 * Native wimits wepowted by dwivews fwom ATI suggest size 256 (i.e. 4KB),
 * wheweas the diffewence between known addwesses suggests size 512.
 *
 * Stawting at addwess UPWOAD_PAWAMETEWS: Vewtex pwogwam pawametews.
 * Native wepowted wimits and the VPI wayout suggest size 256, wheweas
 * diffewence between known addwesses suggests size 512.
 *
 * At addwess UPWOAD_POINTSIZE is a vectow (0, 0, ps, 0), whewe ps is the
 * fwoating point pointsize. The exact puwpose of this state is uncewtain,
 * as thewe is awso the W300_WE_POINTSIZE wegistew.
 *
 * Muwtipwe vewtex pwogwams and pawametew sets can be woaded at once,
 * which couwd expwain the size discwepancy.
 */
#define W300_VAP_PVS_UPWOAD_ADDWESS         0x2200
#       define W300_PVS_UPWOAD_PWOGWAM           0x00000000
#       define W300_PVS_UPWOAD_PAWAMETEWS        0x00000200
#       define W300_PVS_UPWOAD_POINTSIZE         0x00000406

/* gap */

#define W300_VAP_PVS_UPWOAD_DATA            0x2208

/* END: Upwoad vewtex pwogwam and data */

/* gap */

/* I do not know the puwpose of this wegistew. Howevew, I do know that
 * it is set to 221C_CWEAW fow cweaw opewations and to 221C_NOWMAW
 * fow nowmaw wendewing.
 */
#define W300_VAP_UNKNOWN_221C               0x221C
#       define W300_221C_NOWMAW                  0x00000000
#       define W300_221C_CWEAW                   0x0001C000

/* These seem to be pew-pixew and pew-vewtex X and Y cwipping pwanes. The fiwst
 * pwane is pew-pixew and the second pwane is pew-vewtex.
 *
 * This was detewmined by expewimentation awone but I bewieve it is cowwect.
 *
 * These wegistews awe cawwed X_QUAD0_1_FW to X_QUAD0_4_FW by gwxtest.
 */
#define W300_VAP_CWIP_X_0                   0x2220
#define W300_VAP_CWIP_X_1                   0x2224
#define W300_VAP_CWIP_Y_0                   0x2228
#define W300_VAP_CWIP_Y_1                   0x2230

/* gap */

/* Sometimes, END_OF_PKT and 0x2284=0 awe the onwy commands sent between
 * wendewing commands and ovewwwiting vewtex pwogwam pawametews.
 * Thewefowe, I suspect wwiting zewo to 0x2284 synchwonizes the engine and
 * avoids bugs caused by stiww wunning shadews weading bad data fwom memowy.
 */
#define W300_VAP_PVS_STATE_FWUSH_WEG        0x2284

/* Absowutewy no cwue what this wegistew is about. */
#define W300_VAP_UNKNOWN_2288               0x2288
#       define W300_2288_W300                    0x00750000 /* -- nh */
#       define W300_2288_WV350                   0x0000FFFF /* -- Vwadimiw */

/* gap */

/* Addwesses awe wewative to the vewtex pwogwam instwuction awea of the
 * memowy bank. PWOGWAM_END points to the wast instwuction of the active
 * pwogwam
 *
 * The meaning of the two UNKNOWN fiewds is obviouswy not known. Howevew,
 * expewiments so faw have shown that both *must* point to an instwuction
 * inside the vewtex pwogwam, othewwise the GPU wocks up.
 *
 * fgwwx usuawwy sets CNTW_3_UNKNOWN to the end of the pwogwam and
 * W300_PVS_CNTW_1_POS_END_SHIFT points to instwuction whewe wast wwite to
 * position takes pwace.
 *
 * Most wikewy this is used to ignowe west of the pwogwam in cases
 * whewe gwoup of vewts awent visibwe. Fow some weason this "section"
 * is sometimes accepted othew instwuction that have no wewationship with
 * position cawcuwations.
 */
#define W300_VAP_PVS_CNTW_1                 0x22D0
#       define W300_PVS_CNTW_1_PWOGWAM_STAWT_SHIFT   0
#       define W300_PVS_CNTW_1_POS_END_SHIFT         10
#       define W300_PVS_CNTW_1_PWOGWAM_END_SHIFT     20
/* Addwesses awe wewative the vewtex pwogwam pawametews awea. */
#define W300_VAP_PVS_CNTW_2                 0x22D4
#       define W300_PVS_CNTW_2_PAWAM_OFFSET_SHIFT 0
#       define W300_PVS_CNTW_2_PAWAM_COUNT_SHIFT  16
#define W300_VAP_PVS_CNTW_3	           0x22D8
#       define W300_PVS_CNTW_3_PWOGWAM_UNKNOWN_SHIFT 10
#       define W300_PVS_CNTW_3_PWOGWAM_UNKNOWN2_SHIFT 0

/* The entiwe wange fwom 0x2300 to 0x2AC incwusive seems to be used fow
 * immediate vewtices
 */
#define W300_VAP_VTX_COWOW_W                0x2464
#define W300_VAP_VTX_COWOW_G                0x2468
#define W300_VAP_VTX_COWOW_B                0x246C
#define W300_VAP_VTX_POS_0_X_1              0x2490 /* used fow gwVewtex2*() */
#define W300_VAP_VTX_POS_0_Y_1              0x2494
#define W300_VAP_VTX_COWOW_PKD              0x249C /* WGBA */
#define W300_VAP_VTX_POS_0_X_2              0x24A0 /* used fow gwVewtex3*() */
#define W300_VAP_VTX_POS_0_Y_2              0x24A4
#define W300_VAP_VTX_POS_0_Z_2              0x24A8
/* wwite 0 to indicate end of packet? */
#define W300_VAP_VTX_END_OF_PKT             0x24AC

/* gap */

/* These awe vawues fwom w300_weg/w300_weg.h - they awe known to be cowwect
 * and awe hewe so we can use one wegistew fiwe instead of sevewaw
 * - Vwadimiw
 */
#define W300_GB_VAP_WASTEW_VTX_FMT_0	0x4000
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__POS_PWESENT	(1<<0)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__COWOW_0_PWESENT	(1<<1)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__COWOW_1_PWESENT	(1<<2)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__COWOW_2_PWESENT	(1<<3)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__COWOW_3_PWESENT	(1<<4)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__COWOW_SPACE	(0xf<<5)
#	define W300_GB_VAP_WASTEW_VTX_FMT_0__PT_SIZE_PWESENT	(0x1<<16)

#define W300_GB_VAP_WASTEW_VTX_FMT_1	0x4004
	/* each of the fowwowing is 3 bits wide, specifies numbew
	   of components */
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_0_COMP_CNT_SHIFT	0
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_1_COMP_CNT_SHIFT	3
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_2_COMP_CNT_SHIFT	6
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_3_COMP_CNT_SHIFT	9
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_4_COMP_CNT_SHIFT	12
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_5_COMP_CNT_SHIFT	15
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_6_COMP_CNT_SHIFT	18
#	define W300_GB_VAP_WASTEW_VTX_FMT_1__TEX_7_COMP_CNT_SHIFT	21

/* UNK30 seems to enabwes point to quad twansfowmation on textuwes
 * (ow something cwosewy wewated to that).
 * This bit is wathew fataw at the time being due to wackings at pixew
 * shadew side
 */
#define W300_GB_ENABWE	0x4008
#	define W300_GB_POINT_STUFF_ENABWE	(1<<0)
#	define W300_GB_WINE_STUFF_ENABWE	(1<<1)
#	define W300_GB_TWIANGWE_STUFF_ENABWE	(1<<2)
#	define W300_GB_STENCIW_AUTO_ENABWE	(1<<4)
#	define W300_GB_UNK31			(1<<31)
	/* each of the fowwowing is 2 bits wide */
#define W300_GB_TEX_WEPWICATE	0
#define W300_GB_TEX_ST		1
#define W300_GB_TEX_STW		2
#	define W300_GB_TEX0_SOUWCE_SHIFT	16
#	define W300_GB_TEX1_SOUWCE_SHIFT	18
#	define W300_GB_TEX2_SOUWCE_SHIFT	20
#	define W300_GB_TEX3_SOUWCE_SHIFT	22
#	define W300_GB_TEX4_SOUWCE_SHIFT	24
#	define W300_GB_TEX5_SOUWCE_SHIFT	26
#	define W300_GB_TEX6_SOUWCE_SHIFT	28
#	define W300_GB_TEX7_SOUWCE_SHIFT	30

/* MSPOS - positions fow muwtisampwe antiawiasing (?) */
#define W300_GB_MSPOS0	0x4010
	/* shifts - each of the fiewds is 4 bits */
#	define W300_GB_MSPOS0__MS_X0_SHIFT	0
#	define W300_GB_MSPOS0__MS_Y0_SHIFT	4
#	define W300_GB_MSPOS0__MS_X1_SHIFT	8
#	define W300_GB_MSPOS0__MS_Y1_SHIFT	12
#	define W300_GB_MSPOS0__MS_X2_SHIFT	16
#	define W300_GB_MSPOS0__MS_Y2_SHIFT	20
#	define W300_GB_MSPOS0__MSBD0_Y		24
#	define W300_GB_MSPOS0__MSBD0_X		28

#define W300_GB_MSPOS1	0x4014
#	define W300_GB_MSPOS1__MS_X3_SHIFT	0
#	define W300_GB_MSPOS1__MS_Y3_SHIFT	4
#	define W300_GB_MSPOS1__MS_X4_SHIFT	8
#	define W300_GB_MSPOS1__MS_Y4_SHIFT	12
#	define W300_GB_MSPOS1__MS_X5_SHIFT	16
#	define W300_GB_MSPOS1__MS_Y5_SHIFT	20
#	define W300_GB_MSPOS1__MSBD1		24


#define W300_GB_TIWE_CONFIG	0x4018
#	define W300_GB_TIWE_ENABWE	(1<<0)
#	define W300_GB_TIWE_PIPE_COUNT_WV300	0
#	define W300_GB_TIWE_PIPE_COUNT_W300	(3<<1)
#	define W300_GB_TIWE_PIPE_COUNT_W420	(7<<1)
#	define W300_GB_TIWE_PIPE_COUNT_WV410	(3<<1)
#	define W300_GB_TIWE_SIZE_8		0
#	define W300_GB_TIWE_SIZE_16		(1<<4)
#	define W300_GB_TIWE_SIZE_32		(2<<4)
#	define W300_GB_SUPEW_SIZE_1		(0<<6)
#	define W300_GB_SUPEW_SIZE_2		(1<<6)
#	define W300_GB_SUPEW_SIZE_4		(2<<6)
#	define W300_GB_SUPEW_SIZE_8		(3<<6)
#	define W300_GB_SUPEW_SIZE_16		(4<<6)
#	define W300_GB_SUPEW_SIZE_32		(5<<6)
#	define W300_GB_SUPEW_SIZE_64		(6<<6)
#	define W300_GB_SUPEW_SIZE_128		(7<<6)
#	define W300_GB_SUPEW_X_SHIFT		9	/* 3 bits wide */
#	define W300_GB_SUPEW_Y_SHIFT		12	/* 3 bits wide */
#	define W300_GB_SUPEW_TIWE_A		0
#	define W300_GB_SUPEW_TIWE_B		(1<<15)
#	define W300_GB_SUBPIXEW_1_12		0
#	define W300_GB_SUBPIXEW_1_16		(1<<16)

#define W300_GB_FIFO_SIZE	0x4024
	/* each of the fowwowing is 2 bits wide */
#define W300_GB_FIFO_SIZE_32	0
#define W300_GB_FIFO_SIZE_64	1
#define W300_GB_FIFO_SIZE_128	2
#define W300_GB_FIFO_SIZE_256	3
#	define W300_SC_IFIFO_SIZE_SHIFT	0
#	define W300_SC_TZFIFO_SIZE_SHIFT	2
#	define W300_SC_BFIFO_SIZE_SHIFT	4

#	define W300_US_OFIFO_SIZE_SHIFT	12
#	define W300_US_WFIFO_SIZE_SHIFT	14
	/* the fowwowing use the same constants as above, but meaning is
	   is times 2 (i.e. instead of 32 wowds it means 64 */
#	define W300_WS_TFIFO_SIZE_SHIFT	6
#	define W300_WS_CFIFO_SIZE_SHIFT	8
#	define W300_US_WAM_SIZE_SHIFT		10
	/* watewmawks, 3 bits wide */
#	define W300_WS_HIGHWATEW_COW_SHIFT	16
#	define W300_WS_HIGHWATEW_TEX_SHIFT	19
#	define W300_OFIFO_HIGHWATEW_SHIFT	22	/* two bits onwy */
#	define W300_CUBE_FIFO_HIGHWATEW_COW_SHIFT	24

#define W300_GB_SEWECT	0x401C
#	define W300_GB_FOG_SEWECT_C0A		0
#	define W300_GB_FOG_SEWECT_C1A		1
#	define W300_GB_FOG_SEWECT_C2A		2
#	define W300_GB_FOG_SEWECT_C3A		3
#	define W300_GB_FOG_SEWECT_1_1_W	4
#	define W300_GB_FOG_SEWECT_Z		5
#	define W300_GB_DEPTH_SEWECT_Z		0
#	define W300_GB_DEPTH_SEWECT_1_1_W	(1<<3)
#	define W300_GB_W_SEWECT_1_W		0
#	define W300_GB_W_SEWECT_1		(1<<4)

#define W300_GB_AA_CONFIG		0x4020
#	define W300_AA_DISABWE			0x00
#	define W300_AA_ENABWE			0x01
#	define W300_AA_SUBSAMPWES_2		0
#	define W300_AA_SUBSAMPWES_3		(1<<1)
#	define W300_AA_SUBSAMPWES_4		(2<<1)
#	define W300_AA_SUBSAMPWES_6		(3<<1)

/* gap */

/* Zewo to fwush caches. */
#define W300_TX_INVAWTAGS                   0x4100
#define W300_TX_FWUSH                       0x0

/* The uppew enabwe bits awe guessed, based on fgwwx wepowted wimits. */
#define W300_TX_ENABWE                      0x4104
#       define W300_TX_ENABWE_0                  (1 << 0)
#       define W300_TX_ENABWE_1                  (1 << 1)
#       define W300_TX_ENABWE_2                  (1 << 2)
#       define W300_TX_ENABWE_3                  (1 << 3)
#       define W300_TX_ENABWE_4                  (1 << 4)
#       define W300_TX_ENABWE_5                  (1 << 5)
#       define W300_TX_ENABWE_6                  (1 << 6)
#       define W300_TX_ENABWE_7                  (1 << 7)
#       define W300_TX_ENABWE_8                  (1 << 8)
#       define W300_TX_ENABWE_9                  (1 << 9)
#       define W300_TX_ENABWE_10                 (1 << 10)
#       define W300_TX_ENABWE_11                 (1 << 11)
#       define W300_TX_ENABWE_12                 (1 << 12)
#       define W300_TX_ENABWE_13                 (1 << 13)
#       define W300_TX_ENABWE_14                 (1 << 14)
#       define W300_TX_ENABWE_15                 (1 << 15)

/* The pointsize is given in muwtipwes of 6. The pointsize can be
 * enowmous: Cweaw() wendews a singwe point that fiwws the entiwe
 * fwamebuffew.
 */
#define W300_WE_POINTSIZE                   0x421C
#       define W300_POINTSIZE_Y_SHIFT            0
#       define W300_POINTSIZE_Y_MASK             (0xFFFF << 0) /* GUESS */
#       define W300_POINTSIZE_X_SHIFT            16
#       define W300_POINTSIZE_X_MASK             (0xFFFF << 16) /* GUESS */
#       define W300_POINTSIZE_MAX             (W300_POINTSIZE_Y_MASK / 6)

/* The wine width is given in muwtipwes of 6.
 * In defauwt mode wines awe cwassified as vewticaw wines.
 * HO: howizontaw
 * VE: vewticaw ow howizontaw
 * HO & VE: no cwassification
 */
#define W300_WE_WINE_CNT                      0x4234
#       define W300_WINESIZE_SHIFT            0
#       define W300_WINESIZE_MASK             (0xFFFF << 0) /* GUESS */
#       define W300_WINESIZE_MAX             (W300_WINESIZE_MASK / 6)
#       define W300_WINE_CNT_HO               (1 << 16)
#       define W300_WINE_CNT_VE               (1 << 17)

/* Some sowt of scawe ow cwamp vawue fow texcoowdwess textuwes. */
#define W300_WE_UNK4238                       0x4238

/* Something shade wewated */
#define W300_WE_SHADE                         0x4274

#define W300_WE_SHADE_MODEW                   0x4278
#	define W300_WE_SHADE_MODEW_SMOOTH     0x3aaaa
#	define W300_WE_SHADE_MODEW_FWAT       0x39595

/* Dangewous */
#define W300_WE_POWYGON_MODE                  0x4288
#	define W300_PM_ENABWED                (1 << 0)
#	define W300_PM_FWONT_POINT            (0 << 0)
#	define W300_PM_BACK_POINT             (0 << 0)
#	define W300_PM_FWONT_WINE             (1 << 4)
#	define W300_PM_FWONT_FIWW             (1 << 5)
#	define W300_PM_BACK_WINE              (1 << 7)
#	define W300_PM_BACK_FIWW              (1 << 8)

/* Fog pawametews */
#define W300_WE_FOG_SCAWE                     0x4294
#define W300_WE_FOG_STAWT                     0x4298

/* Not suwe why thewe awe dupwicate of factow and constant vawues.
 * My best guess so faw is that thewe awe sepawate zbiases fow test and wwite.
 * Owdewing might be wwong.
 * Some of the tests indicate that fgw has a fawwback impwementation of zbias
 * via pixew shadews.
 */
#define W300_WE_ZBIAS_CNTW                    0x42A0 /* GUESS */
#define W300_WE_ZBIAS_T_FACTOW                0x42A4
#define W300_WE_ZBIAS_T_CONSTANT              0x42A8
#define W300_WE_ZBIAS_W_FACTOW                0x42AC
#define W300_WE_ZBIAS_W_CONSTANT              0x42B0

/* This wegistew needs to be set to (1<<1) fow WV350 to cowwectwy
 * pewfowm depth test (see --vb-twiangwes in w300_demo)
 * Don't know about othew chips. - Vwadimiw
 * This is set to 3 when GW_POWYGON_OFFSET_FIWW is on.
 * My guess is that thewe awe two bits fow each zbias pwimitive
 * (FIWW, WINE, POINT).
 *  One to enabwe depth test and one fow depth wwite.
 * Yet this doesn't expwain why depth wwites wowk ...
 */
#define W300_WE_OCCWUSION_CNTW		    0x42B4
#	define W300_OCCWUSION_ON		(1<<1)

#define W300_WE_CUWW_CNTW                   0x42B8
#       define W300_CUWW_FWONT                   (1 << 0)
#       define W300_CUWW_BACK                    (1 << 1)
#       define W300_FWONT_FACE_CCW               (0 << 2)
#       define W300_FWONT_FACE_CW                (1 << 2)


/* BEGIN: Wastewization / Intewpowatows - many guesses */

/* 0_UNKNOWN_18 has awways been set except fow cweaw opewations.
 * TC_CNT is the numbew of incoming textuwe coowdinate sets (i.e. it depends
 * on the vewtex pwogwam, *not* the fwagment pwogwam)
 */
#define W300_WS_CNTW_0                      0x4300
#       define W300_WS_CNTW_TC_CNT_SHIFT         2
#       define W300_WS_CNTW_TC_CNT_MASK          (7 << 2)
	/* numbew of cowow intewpowatows used */
#	define W300_WS_CNTW_CI_CNT_SHIFT         7
#       define W300_WS_CNTW_0_UNKNOWN_18         (1 << 18)
	/* Guess: WS_CNTW_1 howds the index of the highest used WS_WOUTE_n
	   wegistew. */
#define W300_WS_CNTW_1                      0x4304

/* gap */

/* Onwy used fow textuwe coowdinates.
 * Use the souwce fiewd to woute textuwe coowdinate input fwom the
 * vewtex pwogwam to the desiwed intewpowatow. Note that the souwce
 * fiewd is wewative to the outputs the vewtex pwogwam *actuawwy*
 * wwites. If a vewtex pwogwam onwy wwites texcoowd[1], this wiww
 * be souwce index 0.
 * Set INTEWP_USED on aww intewpowatows that pwoduce data used by
 * the fwagment pwogwam. INTEWP_USED wooks wike a swizzwing mask,
 * but I haven't seen it used that way.
 *
 * Note: The _UNKNOWN constants awe awways set in theiw wespective
 * wegistew. I don't know if this is necessawy.
 */
#define W300_WS_INTEWP_0                    0x4310
#define W300_WS_INTEWP_1                    0x4314
#       define W300_WS_INTEWP_1_UNKNOWN          0x40
#define W300_WS_INTEWP_2                    0x4318
#       define W300_WS_INTEWP_2_UNKNOWN          0x80
#define W300_WS_INTEWP_3                    0x431C
#       define W300_WS_INTEWP_3_UNKNOWN          0xC0
#define W300_WS_INTEWP_4                    0x4320
#define W300_WS_INTEWP_5                    0x4324
#define W300_WS_INTEWP_6                    0x4328
#define W300_WS_INTEWP_7                    0x432C
#       define W300_WS_INTEWP_SWC_SHIFT          2
#       define W300_WS_INTEWP_SWC_MASK           (7 << 2)
#       define W300_WS_INTEWP_USED               0x00D10000

/* These DWOWDs contwow how vewtex data is wouted into fwagment pwogwam
 * wegistews, aftew intewpowatows.
 */
#define W300_WS_WOUTE_0                     0x4330
#define W300_WS_WOUTE_1                     0x4334
#define W300_WS_WOUTE_2                     0x4338
#define W300_WS_WOUTE_3                     0x433C /* GUESS */
#define W300_WS_WOUTE_4                     0x4340 /* GUESS */
#define W300_WS_WOUTE_5                     0x4344 /* GUESS */
#define W300_WS_WOUTE_6                     0x4348 /* GUESS */
#define W300_WS_WOUTE_7                     0x434C /* GUESS */
#       define W300_WS_WOUTE_SOUWCE_INTEWP_0     0
#       define W300_WS_WOUTE_SOUWCE_INTEWP_1     1
#       define W300_WS_WOUTE_SOUWCE_INTEWP_2     2
#       define W300_WS_WOUTE_SOUWCE_INTEWP_3     3
#       define W300_WS_WOUTE_SOUWCE_INTEWP_4     4
#       define W300_WS_WOUTE_SOUWCE_INTEWP_5     5 /* GUESS */
#       define W300_WS_WOUTE_SOUWCE_INTEWP_6     6 /* GUESS */
#       define W300_WS_WOUTE_SOUWCE_INTEWP_7     7 /* GUESS */
#       define W300_WS_WOUTE_ENABWE              (1 << 3) /* GUESS */
#       define W300_WS_WOUTE_DEST_SHIFT          6
#       define W300_WS_WOUTE_DEST_MASK           (31 << 6) /* GUESS */

/* Speciaw handwing fow cowow: When the fwagment pwogwam uses cowow,
 * the WOUTE_0_COWOW bit is set and WOUTE_0_COWOW_DEST contains the
 * cowow wegistew index.
 *
 * Appewentwy you may set the W300_WS_WOUTE_0_COWOW bit, but not pwovide any
 * W300_WS_WOUTE_0_COWOW_DEST vawue; this setup is used fow cweawing the state.
 * See w300_ioctw.c:w300EmitCweawState. I'm not suwe if this setup is stwictwy
 * cowwect ow not. - Owivew.
 */
#       define W300_WS_WOUTE_0_COWOW             (1 << 14)
#       define W300_WS_WOUTE_0_COWOW_DEST_SHIFT  17
#       define W300_WS_WOUTE_0_COWOW_DEST_MASK   (31 << 17) /* GUESS */
/* As above, but fow secondawy cowow */
#		define W300_WS_WOUTE_1_COWOW1            (1 << 14)
#		define W300_WS_WOUTE_1_COWOW1_DEST_SHIFT 17
#		define W300_WS_WOUTE_1_COWOW1_DEST_MASK  (31 << 17)
#		define W300_WS_WOUTE_1_UNKNOWN11         (1 << 11)
/* END: Wastewization / Intewpowatows - many guesses */

/* Hiewawchicaw Z Enabwe */
#define W300_SC_HYPEWZ                   0x43a4
#	define W300_SC_HYPEWZ_DISABWE     (0 << 0)
#	define W300_SC_HYPEWZ_ENABWE      (1 << 0)
#	define W300_SC_HYPEWZ_MIN         (0 << 1)
#	define W300_SC_HYPEWZ_MAX         (1 << 1)
#	define W300_SC_HYPEWZ_ADJ_256     (0 << 2)
#	define W300_SC_HYPEWZ_ADJ_128     (1 << 2)
#	define W300_SC_HYPEWZ_ADJ_64      (2 << 2)
#	define W300_SC_HYPEWZ_ADJ_32      (3 << 2)
#	define W300_SC_HYPEWZ_ADJ_16      (4 << 2)
#	define W300_SC_HYPEWZ_ADJ_8       (5 << 2)
#	define W300_SC_HYPEWZ_ADJ_4       (6 << 2)
#	define W300_SC_HYPEWZ_ADJ_2       (7 << 2)
#	define W300_SC_HYPEWZ_HZ_Z0MIN_NO (0 << 5)
#	define W300_SC_HYPEWZ_HZ_Z0MIN    (1 << 5)
#	define W300_SC_HYPEWZ_HZ_Z0MAX_NO (0 << 6)
#	define W300_SC_HYPEWZ_HZ_Z0MAX    (1 << 6)

#define W300_SC_EDGEWUWE                 0x43a8

/* BEGIN: Scissows and cwipwects */

/* Thewe awe fouw cwipping wectangwes. Theiw cownew coowdinates awe incwusive.
 * Evewy pixew is assigned a numbew fwom 0 and 15 by setting bits 0-3 depending
 * on whethew the pixew is inside cwipwects 0-3, wespectivewy. Fow exampwe,
 * if a pixew is inside cwipwects 0 and 1, but outside 2 and 3, it is assigned
 * the numbew 3 (binawy 0011).
 * Iff the bit cowwesponding to the pixew's numbew in WE_CWIPWECT_CNTW is set,
 * the pixew is wastewized.
 *
 * In addition to this, thewe is a scissows wectangwe. Onwy pixews inside the
 * scissows wectangwe awe dwawn. (coowdinates awe incwusive)
 *
 * Fow some weason, the top-weft cownew of the fwamebuffew is at (1440, 1440)
 * fow the puwpose of cwipping and scissows.
 */
#define W300_WE_CWIPWECT_TW_0               0x43B0
#define W300_WE_CWIPWECT_BW_0               0x43B4
#define W300_WE_CWIPWECT_TW_1               0x43B8
#define W300_WE_CWIPWECT_BW_1               0x43BC
#define W300_WE_CWIPWECT_TW_2               0x43C0
#define W300_WE_CWIPWECT_BW_2               0x43C4
#define W300_WE_CWIPWECT_TW_3               0x43C8
#define W300_WE_CWIPWECT_BW_3               0x43CC
#       define W300_CWIPWECT_OFFSET              1440
#       define W300_CWIPWECT_MASK                0x1FFF
#       define W300_CWIPWECT_X_SHIFT             0
#       define W300_CWIPWECT_X_MASK              (0x1FFF << 0)
#       define W300_CWIPWECT_Y_SHIFT             13
#       define W300_CWIPWECT_Y_MASK              (0x1FFF << 13)
#define W300_WE_CWIPWECT_CNTW               0x43D0
#       define W300_CWIP_OUT                     (1 << 0)
#       define W300_CWIP_0                       (1 << 1)
#       define W300_CWIP_1                       (1 << 2)
#       define W300_CWIP_10                      (1 << 3)
#       define W300_CWIP_2                       (1 << 4)
#       define W300_CWIP_20                      (1 << 5)
#       define W300_CWIP_21                      (1 << 6)
#       define W300_CWIP_210                     (1 << 7)
#       define W300_CWIP_3                       (1 << 8)
#       define W300_CWIP_30                      (1 << 9)
#       define W300_CWIP_31                      (1 << 10)
#       define W300_CWIP_310                     (1 << 11)
#       define W300_CWIP_32                      (1 << 12)
#       define W300_CWIP_320                     (1 << 13)
#       define W300_CWIP_321                     (1 << 14)
#       define W300_CWIP_3210                    (1 << 15)

/* gap */

#define W300_WE_SCISSOWS_TW                 0x43E0
#define W300_WE_SCISSOWS_BW                 0x43E4
#       define W300_SCISSOWS_OFFSET              1440
#       define W300_SCISSOWS_X_SHIFT             0
#       define W300_SCISSOWS_X_MASK              (0x1FFF << 0)
#       define W300_SCISSOWS_Y_SHIFT             13
#       define W300_SCISSOWS_Y_MASK              (0x1FFF << 13)
/* END: Scissows and cwipwects */

/* BEGIN: Textuwe specification */

/*
 * The textuwe specification dwowds awe gwouped by meaning and not by textuwe
 * unit. This means that e.g. the offset fow textuwe image unit N is found in
 * wegistew TX_OFFSET_0 + (4*N)
 */
#define W300_TX_FIWTEW_0                    0x4400
#       define W300_TX_WEPEAT                    0
#       define W300_TX_MIWWOWED                  1
#       define W300_TX_CWAMP                     4
#       define W300_TX_CWAMP_TO_EDGE             2
#       define W300_TX_CWAMP_TO_BOWDEW           6
#       define W300_TX_WWAP_S_SHIFT              0
#       define W300_TX_WWAP_S_MASK               (7 << 0)
#       define W300_TX_WWAP_T_SHIFT              3
#       define W300_TX_WWAP_T_MASK               (7 << 3)
#       define W300_TX_WWAP_Q_SHIFT              6
#       define W300_TX_WWAP_Q_MASK               (7 << 6)
#       define W300_TX_MAG_FIWTEW_NEAWEST        (1 << 9)
#       define W300_TX_MAG_FIWTEW_WINEAW         (2 << 9)
#       define W300_TX_MAG_FIWTEW_MASK           (3 << 9)
#       define W300_TX_MIN_FIWTEW_NEAWEST        (1 << 11)
#       define W300_TX_MIN_FIWTEW_WINEAW         (2 << 11)
#	define W300_TX_MIN_FIWTEW_NEAWEST_MIP_NEAWEST       (5  <<  11)
#	define W300_TX_MIN_FIWTEW_NEAWEST_MIP_WINEAW        (9  <<  11)
#	define W300_TX_MIN_FIWTEW_WINEAW_MIP_NEAWEST        (6  <<  11)
#	define W300_TX_MIN_FIWTEW_WINEAW_MIP_WINEAW         (10 <<  11)

/* NOTE: NEAWEST doesn't seem to exist.
 * Im not seting MAG_FIWTEW_MASK and (3 << 11) on fow aww
 * anisotwopy modes because that wouwd void sewected mag fiwtew
 */
#	define W300_TX_MIN_FIWTEW_ANISO_NEAWEST             (0 << 13)
#	define W300_TX_MIN_FIWTEW_ANISO_WINEAW              (0 << 13)
#	define W300_TX_MIN_FIWTEW_ANISO_NEAWEST_MIP_NEAWEST (1 << 13)
#	define W300_TX_MIN_FIWTEW_ANISO_NEAWEST_MIP_WINEAW  (2 << 13)
#       define W300_TX_MIN_FIWTEW_MASK   ( (15 << 11) | (3 << 13) )
#	define W300_TX_MAX_ANISO_1_TO_1  (0 << 21)
#	define W300_TX_MAX_ANISO_2_TO_1  (2 << 21)
#	define W300_TX_MAX_ANISO_4_TO_1  (4 << 21)
#	define W300_TX_MAX_ANISO_8_TO_1  (6 << 21)
#	define W300_TX_MAX_ANISO_16_TO_1 (8 << 21)
#	define W300_TX_MAX_ANISO_MASK    (14 << 21)

#define W300_TX_FIWTEW1_0                      0x4440
#	define W300_CHWOMA_KEY_MODE_DISABWE    0
#	define W300_CHWOMA_KEY_FOWCE	       1
#	define W300_CHWOMA_KEY_BWEND           2
#	define W300_MC_WOUND_NOWMAW            (0<<2)
#	define W300_MC_WOUND_MPEG4             (1<<2)
#	define W300_WOD_BIAS_MASK	    0x1fff
#	define W300_EDGE_ANISO_EDGE_DIAG       (0<<13)
#	define W300_EDGE_ANISO_EDGE_ONWY       (1<<13)
#	define W300_MC_COOWD_TWUNCATE_DISABWE  (0<<14)
#	define W300_MC_COOWD_TWUNCATE_MPEG     (1<<14)
#	define W300_TX_TWI_PEWF_0_8            (0<<15)
#	define W300_TX_TWI_PEWF_1_8            (1<<15)
#	define W300_TX_TWI_PEWF_1_4            (2<<15)
#	define W300_TX_TWI_PEWF_3_8            (3<<15)
#	define W300_ANISO_THWESHOWD_MASK       (7<<17)

#define W300_TX_SIZE_0                      0x4480
#       define W300_TX_WIDTHMASK_SHIFT           0
#       define W300_TX_WIDTHMASK_MASK            (2047 << 0)
#       define W300_TX_HEIGHTMASK_SHIFT          11
#       define W300_TX_HEIGHTMASK_MASK           (2047 << 11)
#       define W300_TX_UNK23                     (1 << 23)
#       define W300_TX_MAX_MIP_WEVEW_SHIFT       26
#       define W300_TX_MAX_MIP_WEVEW_MASK        (0xf << 26)
#       define W300_TX_SIZE_PWOJECTED            (1<<30)
#       define W300_TX_SIZE_TXPITCH_EN           (1<<31)
#define W300_TX_FOWMAT_0                    0x44C0
	/* The intewpwetation of the fowmat wowd by Wwadimiw van dew Waan */
	/* The X, Y, Z and W wefew to the wayout of the components.
	   They awe given meanings as W, G, B and Awpha by the swizzwe
	   specification */
#	define W300_TX_FOWMAT_X8		    0x0
#	define W300_TX_FOWMAT_X16		    0x1
#	define W300_TX_FOWMAT_Y4X4		    0x2
#	define W300_TX_FOWMAT_Y8X8		    0x3
#	define W300_TX_FOWMAT_Y16X16		    0x4
#	define W300_TX_FOWMAT_Z3Y3X2		    0x5
#	define W300_TX_FOWMAT_Z5Y6X5		    0x6
#	define W300_TX_FOWMAT_Z6Y5X5		    0x7
#	define W300_TX_FOWMAT_Z11Y11X10		    0x8
#	define W300_TX_FOWMAT_Z10Y11X11		    0x9
#	define W300_TX_FOWMAT_W4Z4Y4X4		    0xA
#	define W300_TX_FOWMAT_W1Z5Y5X5		    0xB
#	define W300_TX_FOWMAT_W8Z8Y8X8		    0xC
#	define W300_TX_FOWMAT_W2Z10Y10X10	    0xD
#	define W300_TX_FOWMAT_W16Z16Y16X16	    0xE
#	define W300_TX_FOWMAT_DXT1		    0xF
#	define W300_TX_FOWMAT_DXT3		    0x10
#	define W300_TX_FOWMAT_DXT5		    0x11
#	define W300_TX_FOWMAT_D3DMFT_CxV8U8	    0x12     /* no swizzwe */
#	define W300_TX_FOWMAT_A8W8G8B8		    0x13     /* no swizzwe */
#	define W300_TX_FOWMAT_B8G8_B8G8		    0x14     /* no swizzwe */
#	define W300_TX_FOWMAT_G8W8_G8B8		    0x15     /* no swizzwe */
	/* 0x16 - some 16 bit gween fowmat.. ?? */
#	define W300_TX_FOWMAT_UNK25		   (1 << 25) /* no swizzwe */
#	define W300_TX_FOWMAT_CUBIC_MAP		   (1 << 26)

	/* gap */
	/* Fwoating point fowmats */
	/* Note - hawdwawe suppowts both 16 and 32 bit fwoating point */
#	define W300_TX_FOWMAT_FW_I16		    0x18
#	define W300_TX_FOWMAT_FW_I16A16		    0x19
#	define W300_TX_FOWMAT_FW_W16G16B16A16	    0x1A
#	define W300_TX_FOWMAT_FW_I32		    0x1B
#	define W300_TX_FOWMAT_FW_I32A32		    0x1C
#	define W300_TX_FOWMAT_FW_W32G32B32A32	    0x1D
#	define W300_TX_FOWMAT_ATI2N		    0x1F
	/* awpha modes, convenience mostwy */
	/* if you have awpha, pick constant appwopwiate to the
	   numbew of channews (1 fow I8, 2 fow I8A8, 4 fow W8G8B8A8, etc */
#	define W300_TX_FOWMAT_AWPHA_1CH		    0x000
#	define W300_TX_FOWMAT_AWPHA_2CH		    0x200
#	define W300_TX_FOWMAT_AWPHA_4CH		    0x600
#	define W300_TX_FOWMAT_AWPHA_NONE	    0xA00
	/* Swizzwing */
	/* constants */
#	define W300_TX_FOWMAT_X		0
#	define W300_TX_FOWMAT_Y		1
#	define W300_TX_FOWMAT_Z		2
#	define W300_TX_FOWMAT_W		3
#	define W300_TX_FOWMAT_ZEWO	4
#	define W300_TX_FOWMAT_ONE	5
	/* 2.0*Z, evewything above 1.0 is set to 0.0 */
#	define W300_TX_FOWMAT_CUT_Z	6
	/* 2.0*W, evewything above 1.0 is set to 0.0 */
#	define W300_TX_FOWMAT_CUT_W	7

#	define W300_TX_FOWMAT_B_SHIFT	18
#	define W300_TX_FOWMAT_G_SHIFT	15
#	define W300_TX_FOWMAT_W_SHIFT	12
#	define W300_TX_FOWMAT_A_SHIFT	9
	/* Convenience macwo to take cawe of wayout and swizzwing */
#	define W300_EASY_TX_FOWMAT(B, G, W, A, FMT)	(		\
		((W300_TX_FOWMAT_##B)<<W300_TX_FOWMAT_B_SHIFT)		\
		| ((W300_TX_FOWMAT_##G)<<W300_TX_FOWMAT_G_SHIFT)	\
		| ((W300_TX_FOWMAT_##W)<<W300_TX_FOWMAT_W_SHIFT)	\
		| ((W300_TX_FOWMAT_##A)<<W300_TX_FOWMAT_A_SHIFT)	\
		| (W300_TX_FOWMAT_##FMT)				\
		)
	/* These can be OWed with wesuwt of W300_EASY_TX_FOWMAT()
	   We don't weawwy know what they do. Take vawues fwom a
           constant cowow ? */
#	define W300_TX_FOWMAT_CONST_X		(1<<5)
#	define W300_TX_FOWMAT_CONST_Y		(2<<5)
#	define W300_TX_FOWMAT_CONST_Z		(4<<5)
#	define W300_TX_FOWMAT_CONST_W		(8<<5)

#	define W300_TX_FOWMAT_YUV_MODE		0x00800000

#define W300_TX_PITCH_0			    0x4500 /* obvious missing in gap */
#define W300_TX_OFFSET_0                    0x4540
	/* BEGIN: Guess fwom W200 */
#       define W300_TXO_ENDIAN_NO_SWAP           (0 << 0)
#       define W300_TXO_ENDIAN_BYTE_SWAP         (1 << 0)
#       define W300_TXO_ENDIAN_WOWD_SWAP         (2 << 0)
#       define W300_TXO_ENDIAN_HAWFDW_SWAP       (3 << 0)
#       define W300_TXO_MACWO_TIWE               (1 << 2)
#       define W300_TXO_MICWO_TIWE               (1 << 3)
#       define W300_TXO_MICWO_TIWE_SQUAWE        (2 << 3)
#       define W300_TXO_OFFSET_MASK              0xffffffe0
#       define W300_TXO_OFFSET_SHIFT             5
	/* END: Guess fwom W200 */

/* 32 bit chwoma key */
#define W300_TX_CHWOMA_KEY_0                      0x4580
/* ff00ff00 == { 0, 1.0, 0, 1.0 } */
#define W300_TX_BOWDEW_COWOW_0              0x45C0

/* END: Textuwe specification */

/* BEGIN: Fwagment pwogwam instwuction set */

/* Fwagment pwogwams awe wwitten diwectwy into wegistew space.
 * Thewe awe sepawate instwuction stweams fow textuwe instwuctions and AWU
 * instwuctions.
 * In owdew to synchwonize these stweams, the pwogwam is divided into up
 * to 4 nodes. Each node begins with a numbew of TEX opewations, fowwowed
 * by a numbew of AWU opewations.
 * The fiwst node can have zewo TEX ops, aww subsequent nodes must have at
 * weast
 * one TEX ops.
 * Aww nodes must have at weast one AWU op.
 *
 * The index of the wast node is stowed in PFS_CNTW_0: A vawue of 0 means
 * 1 node, a vawue of 3 means 4 nodes.
 * The totaw amount of instwuctions is defined in PFS_CNTW_2. The offsets awe
 * offsets into the wespective instwuction stweams, whiwe *_END points to the
 * wast instwuction wewative to this offset.
 */
#define W300_PFS_CNTW_0                     0x4600
#       define W300_PFS_CNTW_WAST_NODES_SHIFT    0
#       define W300_PFS_CNTW_WAST_NODES_MASK     (3 << 0)
#       define W300_PFS_CNTW_FIWST_NODE_HAS_TEX  (1 << 3)
#define W300_PFS_CNTW_1                     0x4604
/* Thewe is an unshifted vawue hewe which has so faw awways been equaw to the
 * index of the highest used tempowawy wegistew.
 */
#define W300_PFS_CNTW_2                     0x4608
#       define W300_PFS_CNTW_AWU_OFFSET_SHIFT    0
#       define W300_PFS_CNTW_AWU_OFFSET_MASK     (63 << 0)
#       define W300_PFS_CNTW_AWU_END_SHIFT       6
#       define W300_PFS_CNTW_AWU_END_MASK        (63 << 6)
#       define W300_PFS_CNTW_TEX_OFFSET_SHIFT    12
#       define W300_PFS_CNTW_TEX_OFFSET_MASK     (31 << 12) /* GUESS */
#       define W300_PFS_CNTW_TEX_END_SHIFT       18
#       define W300_PFS_CNTW_TEX_END_MASK        (31 << 18) /* GUESS */

/* gap */

/* Nodes awe stowed backwawds. The wast active node is awways stowed in
 * PFS_NODE_3.
 * Exampwe: In a 2-node pwogwam, NODE_0 and NODE_1 awe set to 0. The
 * fiwst node is stowed in NODE_2, the second node is stowed in NODE_3.
 *
 * Offsets awe wewative to the mastew offset fwom PFS_CNTW_2.
 */
#define W300_PFS_NODE_0                     0x4610
#define W300_PFS_NODE_1                     0x4614
#define W300_PFS_NODE_2                     0x4618
#define W300_PFS_NODE_3                     0x461C
#       define W300_PFS_NODE_AWU_OFFSET_SHIFT    0
#       define W300_PFS_NODE_AWU_OFFSET_MASK     (63 << 0)
#       define W300_PFS_NODE_AWU_END_SHIFT       6
#       define W300_PFS_NODE_AWU_END_MASK        (63 << 6)
#       define W300_PFS_NODE_TEX_OFFSET_SHIFT    12
#       define W300_PFS_NODE_TEX_OFFSET_MASK     (31 << 12)
#       define W300_PFS_NODE_TEX_END_SHIFT       17
#       define W300_PFS_NODE_TEX_END_MASK        (31 << 17)
#		define W300_PFS_NODE_OUTPUT_COWOW        (1 << 22)
#		define W300_PFS_NODE_OUTPUT_DEPTH        (1 << 23)

/* TEX
 * As faw as I can teww, textuwe instwuctions cannot wwite into output
 * wegistews diwectwy. A subsequent AWU instwuction is awways necessawy,
 * even if it's just MAD o0, w0, 1, 0
 */
#define W300_PFS_TEXI_0                     0x4620
#	define W300_FPITX_SWC_SHIFT              0
#	define W300_FPITX_SWC_MASK               (31 << 0)
	/* GUESS */
#	define W300_FPITX_SWC_CONST              (1 << 5)
#	define W300_FPITX_DST_SHIFT              6
#	define W300_FPITX_DST_MASK               (31 << 6)
#	define W300_FPITX_IMAGE_SHIFT            11
	/* GUESS based on wayout and native wimits */
#       define W300_FPITX_IMAGE_MASK             (15 << 11)
/* Unsuwe if these awe opcodes, ow some kind of bitfiewd, but this is how
 * they wewe set when I checked
 */
#	define W300_FPITX_OPCODE_SHIFT		15
#		define W300_FPITX_OP_TEX	1
#		define W300_FPITX_OP_KIW	2
#		define W300_FPITX_OP_TXP	3
#		define W300_FPITX_OP_TXB	4
#	define W300_FPITX_OPCODE_MASK           (7 << 15)

/* AWU
 * The AWU instwuctions wegistew bwocks awe enumewated accowding to the owdew
 * in which fgwwx. I assume thewe is space fow 64 instwuctions, since
 * each bwock has space fow a maximum of 64 DWOWDs, and this matches wepowted
 * native wimits.
 *
 * The basic functionaw bwock seems to be one MAD fow each cowow and awpha,
 * and an addew that adds aww components aftew the MUW.
 *  - ADD, MUW, MAD etc.: use MAD with appwopwiate neutwaw opewands
 *  - DP4: Use OUTC_DP4, OUTA_DP4
 *  - DP3: Use OUTC_DP3, OUTA_DP4, appwopwiate awpha opewands
 *  - DPH: Use OUTC_DP4, OUTA_DP4, appwopwiate awpha opewands
 *  - CMPH: If AWG2 > 0.5, wetuwn AWG0, ewse wetuwn AWG1
 *  - CMP: If AWG2 < 0, wetuwn AWG1, ewse wetuwn AWG0
 *  - FWW: use FWC+MAD
 *  - XPD: use MAD+MAD
 *  - SGE, SWT: use MAD+CMP
 *  - WSQ: use ABS modifiew fow awgument
 *  - Use OUTC_WEPW_AWPHA to wwite wesuwts of an awpha-onwy opewation
 *    (e.g. WCP) into cowow wegistew
 *  - appawentwy, thewe's no quick DST opewation
 *  - fgwwx set FPI2_UNKNOWN_31 on a "MAD fwagment.cowow, tmp0, tmp1, tmp2"
 *  - fgwwx set FPI2_UNKNOWN_31 on a "MAX w2, w1, c0"
 *  - fgwwx once set FPI0_UNKNOWN_31 on a "FWC w1, w1"
 *
 * Opewand sewection
 * Fiwst stage sewects thwee souwces fwom the avaiwabwe wegistews and
 * constant pawametews. This is defined in INSTW1 (cowow) and INSTW3 (awpha).
 * fgwwx sowts the thwee souwce fiewds: Wegistews befowe constants,
 * wowew indices befowe highew indices; I do not know whethew this is
 * necessawy.
 *
 * fgwwx fiwws unused souwces with "wead constant 0"
 * Accowding to specs, you cannot sewect mowe than two diffewent constants.
 *
 * Second stage sewects the opewands fwom the souwces. This is defined in
 * INSTW0 (cowow) and INSTW2 (awpha). You can awso sewect the speciaw constants
 * zewo and one.
 * Swizzwing and negation happens in this stage, as weww.
 *
 * Impowtant: Cowow and awpha seem to be mostwy sepawate, i.e. theiw souwces
 * sewection appeaws to be fuwwy independent (the wegistew stowage is pwobabwy
 * physicawwy spwit into a cowow and an awpha section).
 * Howevew (because of the appawent physicaw spwit), thewe is some intewaction
 * WWT swizzwing. If, fow exampwe, you want to woad an W component into an
 * Awpha opewand, this W component is taken fwom a *cowow* souwce, not fwom
 * an awpha souwce. The cowwesponding wegistew doesn't even have to appeaw in
 * the awpha souwces wist. (I hope this aww makes sense to you)
 *
 * Destination sewection
 * The destination wegistew index is in FPI1 (cowow) and FPI3 (awpha)
 * togethew with enabwe bits.
 * Thewe awe sepawate enabwe bits fow wwiting into tempowawy wegistews
 * (DSTC_WEG_* /DSTA_WEG) and pwogwam output wegistews (DSTC_OUTPUT_*
 * /DSTA_OUTPUT). You can wwite to both at once, ow not wwite at aww (the
 * same index must be used fow both).
 *
 * Note: Thewe is a speciaw fowm fow WWP
 *  - Awgument owdew is the same as in AWB_fwagment_pwogwam.
 *  - Opewation is MAD
 *  - AWG1 is set to AWGC_SWC1C_WWP/AWGC_SWC1A_WWP
 *  - Set FPI0/FPI2_SPECIAW_WWP
 * Awbitwawy WWP (incwuding suppowt fow swizzwing) wequiwes vaniwwa MAD+MAD
 */
#define W300_PFS_INSTW1_0                   0x46C0
#       define W300_FPI1_SWC0C_SHIFT             0
#       define W300_FPI1_SWC0C_MASK              (31 << 0)
#       define W300_FPI1_SWC0C_CONST             (1 << 5)
#       define W300_FPI1_SWC1C_SHIFT             6
#       define W300_FPI1_SWC1C_MASK              (31 << 6)
#       define W300_FPI1_SWC1C_CONST             (1 << 11)
#       define W300_FPI1_SWC2C_SHIFT             12
#       define W300_FPI1_SWC2C_MASK              (31 << 12)
#       define W300_FPI1_SWC2C_CONST             (1 << 17)
#       define W300_FPI1_SWC_MASK                0x0003ffff
#       define W300_FPI1_DSTC_SHIFT              18
#       define W300_FPI1_DSTC_MASK               (31 << 18)
#		define W300_FPI1_DSTC_WEG_MASK_SHIFT     23
#       define W300_FPI1_DSTC_WEG_X              (1 << 23)
#       define W300_FPI1_DSTC_WEG_Y              (1 << 24)
#       define W300_FPI1_DSTC_WEG_Z              (1 << 25)
#		define W300_FPI1_DSTC_OUTPUT_MASK_SHIFT  26
#       define W300_FPI1_DSTC_OUTPUT_X           (1 << 26)
#       define W300_FPI1_DSTC_OUTPUT_Y           (1 << 27)
#       define W300_FPI1_DSTC_OUTPUT_Z           (1 << 28)

#define W300_PFS_INSTW3_0                   0x47C0
#       define W300_FPI3_SWC0A_SHIFT             0
#       define W300_FPI3_SWC0A_MASK              (31 << 0)
#       define W300_FPI3_SWC0A_CONST             (1 << 5)
#       define W300_FPI3_SWC1A_SHIFT             6
#       define W300_FPI3_SWC1A_MASK              (31 << 6)
#       define W300_FPI3_SWC1A_CONST             (1 << 11)
#       define W300_FPI3_SWC2A_SHIFT             12
#       define W300_FPI3_SWC2A_MASK              (31 << 12)
#       define W300_FPI3_SWC2A_CONST             (1 << 17)
#       define W300_FPI3_SWC_MASK                0x0003ffff
#       define W300_FPI3_DSTA_SHIFT              18
#       define W300_FPI3_DSTA_MASK               (31 << 18)
#       define W300_FPI3_DSTA_WEG                (1 << 23)
#       define W300_FPI3_DSTA_OUTPUT             (1 << 24)
#		define W300_FPI3_DSTA_DEPTH              (1 << 27)

#define W300_PFS_INSTW0_0                   0x48C0
#       define W300_FPI0_AWGC_SWC0C_XYZ          0
#       define W300_FPI0_AWGC_SWC0C_XXX          1
#       define W300_FPI0_AWGC_SWC0C_YYY          2
#       define W300_FPI0_AWGC_SWC0C_ZZZ          3
#       define W300_FPI0_AWGC_SWC1C_XYZ          4
#       define W300_FPI0_AWGC_SWC1C_XXX          5
#       define W300_FPI0_AWGC_SWC1C_YYY          6
#       define W300_FPI0_AWGC_SWC1C_ZZZ          7
#       define W300_FPI0_AWGC_SWC2C_XYZ          8
#       define W300_FPI0_AWGC_SWC2C_XXX          9
#       define W300_FPI0_AWGC_SWC2C_YYY          10
#       define W300_FPI0_AWGC_SWC2C_ZZZ          11
#       define W300_FPI0_AWGC_SWC0A              12
#       define W300_FPI0_AWGC_SWC1A              13
#       define W300_FPI0_AWGC_SWC2A              14
#       define W300_FPI0_AWGC_SWC1C_WWP          15
#       define W300_FPI0_AWGC_ZEWO               20
#       define W300_FPI0_AWGC_ONE                21
	/* GUESS */
#       define W300_FPI0_AWGC_HAWF               22
#       define W300_FPI0_AWGC_SWC0C_YZX          23
#       define W300_FPI0_AWGC_SWC1C_YZX          24
#       define W300_FPI0_AWGC_SWC2C_YZX          25
#       define W300_FPI0_AWGC_SWC0C_ZXY          26
#       define W300_FPI0_AWGC_SWC1C_ZXY          27
#       define W300_FPI0_AWGC_SWC2C_ZXY          28
#       define W300_FPI0_AWGC_SWC0CA_WZY         29
#       define W300_FPI0_AWGC_SWC1CA_WZY         30
#       define W300_FPI0_AWGC_SWC2CA_WZY         31

#       define W300_FPI0_AWG0C_SHIFT             0
#       define W300_FPI0_AWG0C_MASK              (31 << 0)
#       define W300_FPI0_AWG0C_NEG               (1 << 5)
#       define W300_FPI0_AWG0C_ABS               (1 << 6)
#       define W300_FPI0_AWG1C_SHIFT             7
#       define W300_FPI0_AWG1C_MASK              (31 << 7)
#       define W300_FPI0_AWG1C_NEG               (1 << 12)
#       define W300_FPI0_AWG1C_ABS               (1 << 13)
#       define W300_FPI0_AWG2C_SHIFT             14
#       define W300_FPI0_AWG2C_MASK              (31 << 14)
#       define W300_FPI0_AWG2C_NEG               (1 << 19)
#       define W300_FPI0_AWG2C_ABS               (1 << 20)
#       define W300_FPI0_SPECIAW_WWP             (1 << 21)
#       define W300_FPI0_OUTC_MAD                (0 << 23)
#       define W300_FPI0_OUTC_DP3                (1 << 23)
#       define W300_FPI0_OUTC_DP4                (2 << 23)
#       define W300_FPI0_OUTC_MIN                (4 << 23)
#       define W300_FPI0_OUTC_MAX                (5 << 23)
#       define W300_FPI0_OUTC_CMPH               (7 << 23)
#       define W300_FPI0_OUTC_CMP                (8 << 23)
#       define W300_FPI0_OUTC_FWC                (9 << 23)
#       define W300_FPI0_OUTC_WEPW_AWPHA         (10 << 23)
#       define W300_FPI0_OUTC_SAT                (1 << 30)
#       define W300_FPI0_INSEWT_NOP              (1 << 31)

#define W300_PFS_INSTW2_0                   0x49C0
#       define W300_FPI2_AWGA_SWC0C_X            0
#       define W300_FPI2_AWGA_SWC0C_Y            1
#       define W300_FPI2_AWGA_SWC0C_Z            2
#       define W300_FPI2_AWGA_SWC1C_X            3
#       define W300_FPI2_AWGA_SWC1C_Y            4
#       define W300_FPI2_AWGA_SWC1C_Z            5
#       define W300_FPI2_AWGA_SWC2C_X            6
#       define W300_FPI2_AWGA_SWC2C_Y            7
#       define W300_FPI2_AWGA_SWC2C_Z            8
#       define W300_FPI2_AWGA_SWC0A              9
#       define W300_FPI2_AWGA_SWC1A              10
#       define W300_FPI2_AWGA_SWC2A              11
#       define W300_FPI2_AWGA_SWC1A_WWP          15
#       define W300_FPI2_AWGA_ZEWO               16
#       define W300_FPI2_AWGA_ONE                17
	/* GUESS */
#       define W300_FPI2_AWGA_HAWF               18
#       define W300_FPI2_AWG0A_SHIFT             0
#       define W300_FPI2_AWG0A_MASK              (31 << 0)
#       define W300_FPI2_AWG0A_NEG               (1 << 5)
	/* GUESS */
#	define W300_FPI2_AWG0A_ABS		 (1 << 6)
#       define W300_FPI2_AWG1A_SHIFT             7
#       define W300_FPI2_AWG1A_MASK              (31 << 7)
#       define W300_FPI2_AWG1A_NEG               (1 << 12)
	/* GUESS */
#	define W300_FPI2_AWG1A_ABS		 (1 << 13)
#       define W300_FPI2_AWG2A_SHIFT             14
#       define W300_FPI2_AWG2A_MASK              (31 << 14)
#       define W300_FPI2_AWG2A_NEG               (1 << 19)
	/* GUESS */
#	define W300_FPI2_AWG2A_ABS		 (1 << 20)
#       define W300_FPI2_SPECIAW_WWP             (1 << 21)
#       define W300_FPI2_OUTA_MAD                (0 << 23)
#       define W300_FPI2_OUTA_DP4                (1 << 23)
#       define W300_FPI2_OUTA_MIN                (2 << 23)
#       define W300_FPI2_OUTA_MAX                (3 << 23)
#       define W300_FPI2_OUTA_CMP                (6 << 23)
#       define W300_FPI2_OUTA_FWC                (7 << 23)
#       define W300_FPI2_OUTA_EX2                (8 << 23)
#       define W300_FPI2_OUTA_WG2                (9 << 23)
#       define W300_FPI2_OUTA_WCP                (10 << 23)
#       define W300_FPI2_OUTA_WSQ                (11 << 23)
#       define W300_FPI2_OUTA_SAT                (1 << 30)
#       define W300_FPI2_UNKNOWN_31              (1 << 31)
/* END: Fwagment pwogwam instwuction set */

/* Fog state and cowow */
#define W300_WE_FOG_STATE                   0x4BC0
#       define W300_FOG_ENABWE                   (1 << 0)
#	define W300_FOG_MODE_WINEAW              (0 << 1)
#	define W300_FOG_MODE_EXP                 (1 << 1)
#	define W300_FOG_MODE_EXP2                (2 << 1)
#	define W300_FOG_MODE_MASK                (3 << 1)
#define W300_FOG_COWOW_W                    0x4BC8
#define W300_FOG_COWOW_G                    0x4BCC
#define W300_FOG_COWOW_B                    0x4BD0

#define W300_PP_AWPHA_TEST                  0x4BD4
#       define W300_WEF_AWPHA_MASK               0x000000ff
#       define W300_AWPHA_TEST_FAIW              (0 << 8)
#       define W300_AWPHA_TEST_WESS              (1 << 8)
#       define W300_AWPHA_TEST_WEQUAW            (3 << 8)
#       define W300_AWPHA_TEST_EQUAW             (2 << 8)
#       define W300_AWPHA_TEST_GEQUAW            (6 << 8)
#       define W300_AWPHA_TEST_GWEATEW           (4 << 8)
#       define W300_AWPHA_TEST_NEQUAW            (5 << 8)
#       define W300_AWPHA_TEST_PASS              (7 << 8)
#       define W300_AWPHA_TEST_OP_MASK           (7 << 8)
#       define W300_AWPHA_TEST_ENABWE            (1 << 11)

/* gap */

/* Fwagment pwogwam pawametews in 7.16 fwoating point */
#define W300_PFS_PAWAM_0_X                  0x4C00
#define W300_PFS_PAWAM_0_Y                  0x4C04
#define W300_PFS_PAWAM_0_Z                  0x4C08
#define W300_PFS_PAWAM_0_W                  0x4C0C
/* GUESS: PAWAM_31 is wast, based on native wimits wepowted by fgwwx */
#define W300_PFS_PAWAM_31_X                 0x4DF0
#define W300_PFS_PAWAM_31_Y                 0x4DF4
#define W300_PFS_PAWAM_31_Z                 0x4DF8
#define W300_PFS_PAWAM_31_W                 0x4DFC

/* Notes:
 * - AFAIK fgwwx awways sets BWEND_UNKNOWN when bwending is used in
 *   the appwication
 * - AFAIK fgwwx awways sets BWEND_NO_SEPAWATE when CBWEND and ABWEND
 *    awe set to the same
 *   function (both wegistews awe awways set up compwetewy in any case)
 * - Most bwend fwags awe simpwy copied fwom W200 and not tested yet
 */
#define W300_WB3D_CBWEND                    0x4E04
#define W300_WB3D_ABWEND                    0x4E08
/* the fowwowing onwy appeaw in CBWEND */
#       define W300_BWEND_ENABWE                     (1 << 0)
#       define W300_BWEND_UNKNOWN                    (3 << 1)
#       define W300_BWEND_NO_SEPAWATE                (1 << 3)
/* the fowwowing awe shawed between CBWEND and ABWEND */
#       define W300_FCN_MASK                         (3  << 12)
#       define W300_COMB_FCN_ADD_CWAMP               (0  << 12)
#       define W300_COMB_FCN_ADD_NOCWAMP             (1  << 12)
#       define W300_COMB_FCN_SUB_CWAMP               (2  << 12)
#       define W300_COMB_FCN_SUB_NOCWAMP             (3  << 12)
#       define W300_COMB_FCN_MIN                     (4  << 12)
#       define W300_COMB_FCN_MAX                     (5  << 12)
#       define W300_COMB_FCN_WSUB_CWAMP              (6  << 12)
#       define W300_COMB_FCN_WSUB_NOCWAMP            (7  << 12)
#       define W300_BWEND_GW_ZEWO                    (32)
#       define W300_BWEND_GW_ONE                     (33)
#       define W300_BWEND_GW_SWC_COWOW               (34)
#       define W300_BWEND_GW_ONE_MINUS_SWC_COWOW     (35)
#       define W300_BWEND_GW_DST_COWOW               (36)
#       define W300_BWEND_GW_ONE_MINUS_DST_COWOW     (37)
#       define W300_BWEND_GW_SWC_AWPHA               (38)
#       define W300_BWEND_GW_ONE_MINUS_SWC_AWPHA     (39)
#       define W300_BWEND_GW_DST_AWPHA               (40)
#       define W300_BWEND_GW_ONE_MINUS_DST_AWPHA     (41)
#       define W300_BWEND_GW_SWC_AWPHA_SATUWATE      (42)
#       define W300_BWEND_GW_CONST_COWOW             (43)
#       define W300_BWEND_GW_ONE_MINUS_CONST_COWOW   (44)
#       define W300_BWEND_GW_CONST_AWPHA             (45)
#       define W300_BWEND_GW_ONE_MINUS_CONST_AWPHA   (46)
#       define W300_BWEND_MASK                       (63)
#       define W300_SWC_BWEND_SHIFT                  (16)
#       define W300_DST_BWEND_SHIFT                  (24)
#define W300_WB3D_BWEND_COWOW               0x4E10
#define W300_WB3D_COWOWMASK                 0x4E0C
#       define W300_COWOWMASK0_B                 (1<<0)
#       define W300_COWOWMASK0_G                 (1<<1)
#       define W300_COWOWMASK0_W                 (1<<2)
#       define W300_COWOWMASK0_A                 (1<<3)

/* gap */

#define W300_WB3D_COWOWOFFSET0              0x4E28
#       define W300_COWOWOFFSET_MASK             0xFFFFFFF0 /* GUESS */
#define W300_WB3D_COWOWOFFSET1              0x4E2C /* GUESS */
#define W300_WB3D_COWOWOFFSET2              0x4E30 /* GUESS */
#define W300_WB3D_COWOWOFFSET3              0x4E34 /* GUESS */

/* gap */

/* Bit 16: Wawgew tiwes
 * Bit 17: 4x2 tiwes
 * Bit 18: Extwemewy weiwd tiwe wike, but some pixews dupwicated?
 */
#define W300_WB3D_COWOWPITCH0               0x4E38
#       define W300_COWOWPITCH_MASK              0x00001FF8 /* GUESS */
#       define W300_COWOW_TIWE_ENABWE            (1 << 16) /* GUESS */
#       define W300_COWOW_MICWOTIWE_ENABWE       (1 << 17) /* GUESS */
#       define W300_COWOW_MICWOTIWE_SQUAWE_ENABWE (2 << 17)
#       define W300_COWOW_ENDIAN_NO_SWAP         (0 << 18) /* GUESS */
#       define W300_COWOW_ENDIAN_WOWD_SWAP       (1 << 18) /* GUESS */
#       define W300_COWOW_ENDIAN_DWOWD_SWAP      (2 << 18) /* GUESS */
#       define W300_COWOW_FOWMAT_WGB565          (2 << 22)
#       define W300_COWOW_FOWMAT_AWGB8888        (3 << 22)
#define W300_WB3D_COWOWPITCH1               0x4E3C /* GUESS */
#define W300_WB3D_COWOWPITCH2               0x4E40 /* GUESS */
#define W300_WB3D_COWOWPITCH3               0x4E44 /* GUESS */

#define W300_WB3D_AAWESOWVE_OFFSET          0x4E80
#define W300_WB3D_AAWESOWVE_PITCH           0x4E84
#define W300_WB3D_AAWESOWVE_CTW             0x4E88
/* gap */

/* Guess by Vwadimiw.
 * Set to 0A befowe 3D opewations, set to 02 aftewwawds.
 */
/*#define W300_WB3D_DSTCACHE_CTWSTAT          0x4E4C*/
#       define W300_WB3D_DSTCACHE_UNKNOWN_02             0x00000002
#       define W300_WB3D_DSTCACHE_UNKNOWN_0A             0x0000000A

/* gap */
/* Thewe seems to be no "wwite onwy" setting, so use Z-test = AWWAYS
 * fow this.
 * Bit (1<<8) is the "test" bit. so pwain wwite is 6  - vd
 */
#define W300_ZB_CNTW                             0x4F00
#	define W300_STENCIW_ENABWE		 (1 << 0)
#	define W300_Z_ENABWE		         (1 << 1)
#	define W300_Z_WWITE_ENABWE		 (1 << 2)
#	define W300_Z_SIGNED_COMPAWE		 (1 << 3)
#	define W300_STENCIW_FWONT_BACK		 (1 << 4)

#define W300_ZB_ZSTENCIWCNTW                   0x4f04
	/* functions */
#	define W300_ZS_NEVEW			0
#	define W300_ZS_WESS			1
#	define W300_ZS_WEQUAW			2
#	define W300_ZS_EQUAW			3
#	define W300_ZS_GEQUAW			4
#	define W300_ZS_GWEATEW			5
#	define W300_ZS_NOTEQUAW			6
#	define W300_ZS_AWWAYS			7
#       define W300_ZS_MASK                     7
	/* opewations */
#	define W300_ZS_KEEP			0
#	define W300_ZS_ZEWO			1
#	define W300_ZS_WEPWACE			2
#	define W300_ZS_INCW			3
#	define W300_ZS_DECW			4
#	define W300_ZS_INVEWT			5
#	define W300_ZS_INCW_WWAP		6
#	define W300_ZS_DECW_WWAP		7
#	define W300_Z_FUNC_SHIFT		0
	/* fwont and back wefew to opewations done fow fwont
	   and back faces, i.e. sepawate stenciw function suppowt */
#	define W300_S_FWONT_FUNC_SHIFT	        3
#	define W300_S_FWONT_SFAIW_OP_SHIFT	6
#	define W300_S_FWONT_ZPASS_OP_SHIFT	9
#	define W300_S_FWONT_ZFAIW_OP_SHIFT      12
#	define W300_S_BACK_FUNC_SHIFT           15
#	define W300_S_BACK_SFAIW_OP_SHIFT       18
#	define W300_S_BACK_ZPASS_OP_SHIFT       21
#	define W300_S_BACK_ZFAIW_OP_SHIFT       24

#define W300_ZB_STENCIWWEFMASK                        0x4f08
#	define W300_STENCIWWEF_SHIFT       0
#	define W300_STENCIWWEF_MASK        0x000000ff
#	define W300_STENCIWMASK_SHIFT      8
#	define W300_STENCIWMASK_MASK       0x0000ff00
#	define W300_STENCIWWWITEMASK_SHIFT 16
#	define W300_STENCIWWWITEMASK_MASK  0x00ff0000

/* gap */

#define W300_ZB_FOWMAT                             0x4f10
#	define W300_DEPTHFOWMAT_16BIT_INT_Z   (0 << 0)
#	define W300_DEPTHFOWMAT_16BIT_13E3    (1 << 0)
#	define W300_DEPTHFOWMAT_24BIT_INT_Z_8BIT_STENCIW   (2 << 0)
/* wesewved up to (15 << 0) */
#	define W300_INVEWT_13E3_WEADING_ONES  (0 << 4)
#	define W300_INVEWT_13E3_WEADING_ZEWOS (1 << 4)

#define W300_ZB_ZTOP                             0x4F14
#	define W300_ZTOP_DISABWE                 (0 << 0)
#	define W300_ZTOP_ENABWE                  (1 << 0)

/* gap */

#define W300_ZB_ZCACHE_CTWSTAT            0x4f18
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_FWUSH_NO_EFFECT      (0 << 0)
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_FWUSH_FWUSH_AND_FWEE (1 << 0)
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_FWEE_NO_EFFECT       (0 << 1)
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_FWEE_FWEE            (1 << 1)
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_BUSY_IDWE            (0 << 31)
#       define W300_ZB_ZCACHE_CTWSTAT_ZC_BUSY_BUSY            (1 << 31)

#define W300_ZB_BW_CNTW                     0x4f1c
#	define W300_HIZ_DISABWE                              (0 << 0)
#	define W300_HIZ_ENABWE                               (1 << 0)
#	define W300_HIZ_MIN                                  (0 << 1)
#	define W300_HIZ_MAX                                  (1 << 1)
#	define W300_FAST_FIWW_DISABWE                        (0 << 2)
#	define W300_FAST_FIWW_ENABWE                         (1 << 2)
#	define W300_WD_COMP_DISABWE                          (0 << 3)
#	define W300_WD_COMP_ENABWE                           (1 << 3)
#	define W300_WW_COMP_DISABWE                          (0 << 4)
#	define W300_WW_COMP_ENABWE                           (1 << 4)
#	define W300_ZB_CB_CWEAW_WMW                          (0 << 5)
#	define W300_ZB_CB_CWEAW_CACHE_WINEAW                 (1 << 5)
#	define W300_FOWCE_COMPWESSED_STENCIW_VAWUE_DISABWE   (0 << 6)
#	define W300_FOWCE_COMPWESSED_STENCIW_VAWUE_ENABWE    (1 << 6)

#	define W500_ZEQUAW_OPTIMIZE_ENABWE                   (0 << 7)
#	define W500_ZEQUAW_OPTIMIZE_DISABWE                  (1 << 7)
#	define W500_SEQUAW_OPTIMIZE_ENABWE                   (0 << 8)
#	define W500_SEQUAW_OPTIMIZE_DISABWE                  (1 << 8)

#	define W500_BMASK_ENABWE                             (0 << 10)
#	define W500_BMASK_DISABWE                            (1 << 10)
#	define W500_HIZ_EQUAW_WEJECT_DISABWE                 (0 << 11)
#	define W500_HIZ_EQUAW_WEJECT_ENABWE                  (1 << 11)
#	define W500_HIZ_FP_EXP_BITS_DISABWE                  (0 << 12)
#	define W500_HIZ_FP_EXP_BITS_1                        (1 << 12)
#	define W500_HIZ_FP_EXP_BITS_2                        (2 << 12)
#	define W500_HIZ_FP_EXP_BITS_3                        (3 << 12)
#	define W500_HIZ_FP_EXP_BITS_4                        (4 << 12)
#	define W500_HIZ_FP_EXP_BITS_5                        (5 << 12)
#	define W500_HIZ_FP_INVEWT_WEADING_ONES               (0 << 15)
#	define W500_HIZ_FP_INVEWT_WEADING_ZEWOS              (1 << 15)
#	define W500_TIWE_OVEWWWITE_WECOMPWESSION_ENABWE      (0 << 16)
#	define W500_TIWE_OVEWWWITE_WECOMPWESSION_DISABWE     (1 << 16)
#	define W500_CONTIGUOUS_6XAA_SAMPWES_ENABWE           (0 << 17)
#	define W500_CONTIGUOUS_6XAA_SAMPWES_DISABWE          (1 << 17)
#	define W500_PEQ_PACKING_DISABWE                      (0 << 18)
#	define W500_PEQ_PACKING_ENABWE                       (1 << 18)
#	define W500_COVEWED_PTW_MASKING_DISABWE              (0 << 18)
#	define W500_COVEWED_PTW_MASKING_ENABWE               (1 << 18)


/* gap */

/* Z Buffew Addwess Offset.
 * Bits 31 to 5 awe used fow awigned Z buffew addwess offset fow macwo tiwes.
 */
#define W300_ZB_DEPTHOFFSET               0x4f20

/* Z Buffew Pitch and Endian Contwow */
#define W300_ZB_DEPTHPITCH                0x4f24
#       define W300_DEPTHPITCH_MASK              0x00003FFC
#       define W300_DEPTHMACWOTIWE_DISABWE      (0 << 16)
#       define W300_DEPTHMACWOTIWE_ENABWE       (1 << 16)
#       define W300_DEPTHMICWOTIWE_WINEAW       (0 << 17)
#       define W300_DEPTHMICWOTIWE_TIWED        (1 << 17)
#       define W300_DEPTHMICWOTIWE_TIWED_SQUAWE (2 << 17)
#       define W300_DEPTHENDIAN_NO_SWAP         (0 << 18)
#       define W300_DEPTHENDIAN_WOWD_SWAP       (1 << 18)
#       define W300_DEPTHENDIAN_DWOWD_SWAP      (2 << 18)
#       define W300_DEPTHENDIAN_HAWF_DWOWD_SWAP (3 << 18)

/* Z Buffew Cweaw Vawue */
#define W300_ZB_DEPTHCWEAWVAWUE                  0x4f28

#define W300_ZB_ZMASK_OFFSET			 0x4f30
#define W300_ZB_ZMASK_PITCH			 0x4f34
#define W300_ZB_ZMASK_WWINDEX			 0x4f38
#define W300_ZB_ZMASK_DWOWD			 0x4f3c
#define W300_ZB_ZMASK_WDINDEX			 0x4f40

/* Hiewawchicaw Z Memowy Offset */
#define W300_ZB_HIZ_OFFSET                       0x4f44

/* Hiewawchicaw Z Wwite Index */
#define W300_ZB_HIZ_WWINDEX                      0x4f48

/* Hiewawchicaw Z Data */
#define W300_ZB_HIZ_DWOWD                        0x4f4c

/* Hiewawchicaw Z Wead Index */
#define W300_ZB_HIZ_WDINDEX                      0x4f50

/* Hiewawchicaw Z Pitch */
#define W300_ZB_HIZ_PITCH                        0x4f54

/* Z Buffew Z Pass Countew Data */
#define W300_ZB_ZPASS_DATA                       0x4f58

/* Z Buffew Z Pass Countew Addwess */
#define W300_ZB_ZPASS_ADDW                       0x4f5c

/* Depth buffew X and Y coowdinate offset */
#define W300_ZB_DEPTHXY_OFFSET                   0x4f60
#	define W300_DEPTHX_OFFSET_SHIFT  1
#	define W300_DEPTHX_OFFSET_MASK   0x000007FE
#	define W300_DEPTHY_OFFSET_SHIFT  17
#	define W300_DEPTHY_OFFSET_MASK   0x07FE0000

/* Sets the fifo sizes */
#define W500_ZB_FIFO_SIZE                        0x4fd0
#	define W500_OP_FIFO_SIZE_FUWW   (0 << 0)
#	define W500_OP_FIFO_SIZE_HAWF   (1 << 0)
#	define W500_OP_FIFO_SIZE_QUATEW (2 << 0)
#	define W500_OP_FIFO_SIZE_EIGTHS (4 << 0)

/* Stenciw Wefewence Vawue and Mask fow backfacing quads */
/* W300_ZB_STENCIWWEFMASK handwes fwont face */
#define W500_ZB_STENCIWWEFMASK_BF                0x4fd4
#	define W500_STENCIWWEF_SHIFT       0
#	define W500_STENCIWWEF_MASK        0x000000ff
#	define W500_STENCIWMASK_SHIFT      8
#	define W500_STENCIWMASK_MASK       0x0000ff00
#	define W500_STENCIWWWITEMASK_SHIFT 16
#	define W500_STENCIWWWITEMASK_MASK  0x00ff0000

/* BEGIN: Vewtex pwogwam instwuction set */

/* Evewy instwuction is fouw dwowds wong:
 *  DWOWD 0: output and opcode
 *  DWOWD 1: fiwst awgument
 *  DWOWD 2: second awgument
 *  DWOWD 3: thiwd awgument
 *
 * Notes:
 *  - ABS w, a is impwemented as MAX w, a, -a
 *  - MOV is impwemented as ADD to zewo
 *  - XPD is impwemented as MUW + MAD
 *  - FWW is impwemented as FWC + ADD
 *  - appawentwy, fgwwx twies to scheduwe instwuctions so that thewe is at
 *    weast one instwuction between the wwite to a tempowawy and the fiwst
 *    wead fwom said tempowawy; howevew, viowations of this scheduwing awe
 *    awwowed
 *  - wegistew indices seem to be unwewated with OpenGW awiasing to
 *    conventionaw state
 *  - onwy one attwibute and one pawametew can be woaded at a time; howevew,
 *    the same attwibute/pawametew can be used fow mowe than one awgument
 *  - the second softwawe awgument fow POW is the thiwd hawdwawe awgument
 *    (no idea why)
 *  - MAD with onwy tempowawies as input seems to use VPI_OUT_SEWECT_MAD_2
 *
 * Thewe is some magic suwwounding WIT:
 *   The singwe awgument is wepwicated acwoss aww thwee inputs, but swizzwed:
 *     Fiwst awgument: xyzy
 *     Second awgument: xyzx
 *     Thiwd awgument: xyzw
 *   Whenevew the wesuwt is used watew in the fwagment pwogwam, fgwwx fowces
 *   x and w to be 1.0 in the input sewection; I don't know whethew this is
 *   stwictwy necessawy
 */
#define W300_VPI_OUT_OP_DOT                     (1 << 0)
#define W300_VPI_OUT_OP_MUW                     (2 << 0)
#define W300_VPI_OUT_OP_ADD                     (3 << 0)
#define W300_VPI_OUT_OP_MAD                     (4 << 0)
#define W300_VPI_OUT_OP_DST                     (5 << 0)
#define W300_VPI_OUT_OP_FWC                     (6 << 0)
#define W300_VPI_OUT_OP_MAX                     (7 << 0)
#define W300_VPI_OUT_OP_MIN                     (8 << 0)
#define W300_VPI_OUT_OP_SGE                     (9 << 0)
#define W300_VPI_OUT_OP_SWT                     (10 << 0)
	/* Used in GW_POINT_DISTANCE_ATTENUATION_AWB, vectow(scawaw, vectow) */
#define W300_VPI_OUT_OP_UNK12                   (12 << 0)
#define W300_VPI_OUT_OP_AWW                     (13 << 0)
#define W300_VPI_OUT_OP_EXP                     (65 << 0)
#define W300_VPI_OUT_OP_WOG                     (66 << 0)
	/* Used in fog computations, scawaw(scawaw) */
#define W300_VPI_OUT_OP_UNK67                   (67 << 0)
#define W300_VPI_OUT_OP_WIT                     (68 << 0)
#define W300_VPI_OUT_OP_POW                     (69 << 0)
#define W300_VPI_OUT_OP_WCP                     (70 << 0)
#define W300_VPI_OUT_OP_WSQ                     (72 << 0)
	/* Used in GW_POINT_DISTANCE_ATTENUATION_AWB, scawaw(scawaw) */
#define W300_VPI_OUT_OP_UNK73                   (73 << 0)
#define W300_VPI_OUT_OP_EX2                     (75 << 0)
#define W300_VPI_OUT_OP_WG2                     (76 << 0)
#define W300_VPI_OUT_OP_MAD_2                   (128 << 0)
	/* aww temps, vectow(scawaw, vectow, vectow) */
#define W300_VPI_OUT_OP_UNK129                  (129 << 0)

#define W300_VPI_OUT_WEG_CWASS_TEMPOWAWY        (0 << 8)
#define W300_VPI_OUT_WEG_CWASS_ADDW             (1 << 8)
#define W300_VPI_OUT_WEG_CWASS_WESUWT           (2 << 8)
#define W300_VPI_OUT_WEG_CWASS_MASK             (31 << 8)

#define W300_VPI_OUT_WEG_INDEX_SHIFT            13
	/* GUESS based on fgwwx native wimits */
#define W300_VPI_OUT_WEG_INDEX_MASK             (31 << 13)

#define W300_VPI_OUT_WWITE_X                    (1 << 20)
#define W300_VPI_OUT_WWITE_Y                    (1 << 21)
#define W300_VPI_OUT_WWITE_Z                    (1 << 22)
#define W300_VPI_OUT_WWITE_W                    (1 << 23)

#define W300_VPI_IN_WEG_CWASS_TEMPOWAWY         (0 << 0)
#define W300_VPI_IN_WEG_CWASS_ATTWIBUTE         (1 << 0)
#define W300_VPI_IN_WEG_CWASS_PAWAMETEW         (2 << 0)
#define W300_VPI_IN_WEG_CWASS_NONE              (9 << 0)
#define W300_VPI_IN_WEG_CWASS_MASK              (31 << 0)

#define W300_VPI_IN_WEG_INDEX_SHIFT             5
	/* GUESS based on fgwwx native wimits */
#define W300_VPI_IN_WEG_INDEX_MASK              (255 << 5)

/* The W300 can sewect components fwom the input wegistew awbitwawiwy.
 * Use the fowwowing constants, shifted by the component shift you
 * want to sewect
 */
#define W300_VPI_IN_SEWECT_X    0
#define W300_VPI_IN_SEWECT_Y    1
#define W300_VPI_IN_SEWECT_Z    2
#define W300_VPI_IN_SEWECT_W    3
#define W300_VPI_IN_SEWECT_ZEWO 4
#define W300_VPI_IN_SEWECT_ONE  5
#define W300_VPI_IN_SEWECT_MASK 7

#define W300_VPI_IN_X_SHIFT                     13
#define W300_VPI_IN_Y_SHIFT                     16
#define W300_VPI_IN_Z_SHIFT                     19
#define W300_VPI_IN_W_SHIFT                     22

#define W300_VPI_IN_NEG_X                       (1 << 25)
#define W300_VPI_IN_NEG_Y                       (1 << 26)
#define W300_VPI_IN_NEG_Z                       (1 << 27)
#define W300_VPI_IN_NEG_W                       (1 << 28)
/* END: Vewtex pwogwam instwuction set */

/* BEGIN: Packet 3 commands */

/* A pwimitive emission dwowd. */
#define W300_PWIM_TYPE_NONE                     (0 << 0)
#define W300_PWIM_TYPE_POINT                    (1 << 0)
#define W300_PWIM_TYPE_WINE                     (2 << 0)
#define W300_PWIM_TYPE_WINE_STWIP               (3 << 0)
#define W300_PWIM_TYPE_TWI_WIST                 (4 << 0)
#define W300_PWIM_TYPE_TWI_FAN                  (5 << 0)
#define W300_PWIM_TYPE_TWI_STWIP                (6 << 0)
#define W300_PWIM_TYPE_TWI_TYPE2                (7 << 0)
#define W300_PWIM_TYPE_WECT_WIST                (8 << 0)
#define W300_PWIM_TYPE_3VWT_POINT_WIST          (9 << 0)
#define W300_PWIM_TYPE_3VWT_WINE_WIST           (10 << 0)
	/* GUESS (based on w200) */
#define W300_PWIM_TYPE_POINT_SPWITES            (11 << 0)
#define W300_PWIM_TYPE_WINE_WOOP                (12 << 0)
#define W300_PWIM_TYPE_QUADS                    (13 << 0)
#define W300_PWIM_TYPE_QUAD_STWIP               (14 << 0)
#define W300_PWIM_TYPE_POWYGON                  (15 << 0)
#define W300_PWIM_TYPE_MASK                     0xF
#define W300_PWIM_WAWK_IND                      (1 << 4)
#define W300_PWIM_WAWK_WIST                     (2 << 4)
#define W300_PWIM_WAWK_WING                     (3 << 4)
#define W300_PWIM_WAWK_MASK                     (3 << 4)
	/* GUESS (based on w200) */
#define W300_PWIM_COWOW_OWDEW_BGWA              (0 << 6)
#define W300_PWIM_COWOW_OWDEW_WGBA              (1 << 6)
#define W300_PWIM_NUM_VEWTICES_SHIFT            16
#define W300_PWIM_NUM_VEWTICES_MASK             0xffff

/* Dwaw a pwimitive fwom vewtex data in awways woaded via 3D_WOAD_VBPNTW.
 * Two pawametew dwowds:
 * 0. The fiwst pawametew appeaws to be awways 0
 * 1. The second pawametew is a standawd pwimitive emission dwowd.
 */
#define W300_PACKET3_3D_DWAW_VBUF           0x00002800

/* Specify the fuww set of vewtex awways as (addwess, stwide).
 * The fiwst pawametew is the numbew of vewtex awways specified.
 * The west of the command is a vawiabwe wength wist of bwocks, whewe
 * each bwock is thwee dwowds wong and specifies two awways.
 * The fiwst dwowd of a bwock is spwit into two wowds, the wowew significant
 * wowd wefews to the fiwst awway, the mowe significant wowd to the second
 * awway in the bwock.
 * The wow byte of each wowd contains the size of an awway entwy in dwowds,
 * the high byte contains the stwide of the awway.
 * The second dwowd of a bwock contains the pointew to the fiwst awway,
 * the thiwd dwowd of a bwock contains the pointew to the second awway.
 * Note that if the totaw numbew of awways is odd, the thiwd dwowd of
 * the wast bwock is omitted.
 */
#define W300_PACKET3_3D_WOAD_VBPNTW         0x00002F00

#define W300_PACKET3_INDX_BUFFEW            0x00003300
#    define W300_EB_UNK1_SHIFT                      24
#    define W300_EB_UNK1                    (0x80<<24)
#    define W300_EB_UNK2                        0x0810
#define W300_PACKET3_3D_DWAW_VBUF_2         0x00003400
#define W300_PACKET3_3D_DWAW_INDX_2         0x00003600

/* END: Packet 3 commands */


/* Cowow fowmats fow 2d packets
 */
#define W300_CP_COWOW_FOWMAT_CI8	2
#define W300_CP_COWOW_FOWMAT_AWGB1555	3
#define W300_CP_COWOW_FOWMAT_WGB565	4
#define W300_CP_COWOW_FOWMAT_AWGB8888	6
#define W300_CP_COWOW_FOWMAT_WGB332	7
#define W300_CP_COWOW_FOWMAT_WGB8	9
#define W300_CP_COWOW_FOWMAT_AWGB4444	15

/*
 * CP type-3 packets
 */
#define W300_CP_CMD_BITBWT_MUWTI	0xC0009B00

#define W500_VAP_INDEX_OFFSET		0x208c

#define W500_GA_US_VECTOW_INDEX         0x4250
#define W500_GA_US_VECTOW_DATA          0x4254

#define W500_WS_IP_0                    0x4074
#define W500_WS_INST_0                  0x4320

#define W500_US_CONFIG                  0x4600

#define W500_US_FC_CTWW			0x4624
#define W500_US_CODE_ADDW		0x4630

#define W500_WB3D_COWOW_CWEAW_VAWUE_AW  0x46c0
#define W500_WB3D_CONSTANT_COWOW_AW     0x4ef8

#define W300_SU_WEG_DEST                0x42c8
#define WV530_FG_ZBWEG_DEST             0x4be8
#define W300_ZB_ZPASS_DATA              0x4f58
#define W300_ZB_ZPASS_ADDW              0x4f5c

#endif /* _W300_WEG_H */
