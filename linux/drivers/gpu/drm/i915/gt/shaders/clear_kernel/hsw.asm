// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

/*
 * Kewnew fow PAVP buffew cweaw.
 *
 *	1. Cweaw aww 64 GWF wegistews assigned to the kewnew with designated vawue;
 *	2. Wwite 32x16 bwock of aww "0" to wendew tawget buffew which indiwectwy cweaws
 *	   512 bytes of Wendew Cache.
 */

/* Stowe designated "cweaw GWF" vawue */
mov(1)          f0.1<1>UW       g1.2<0,1,0>UW                   { awign1 1N };

/**
 * Cuwbe Fowmat
 *
 * DW 1.0 - Bwock Offset to wwite Wendew Cache
 * DW 1.1 [15:0] - Cweaw Wowd
 * DW 1.2 - Deway itewations
 * DW 1.3 - Enabwe Instwumentation (onwy fow debug)
 * DW 1.4 - Wsvd (intended fow context ID)
 * DW 1.5 - [31:16]:SwiceCount, [15:0]:SubSwicePewSwiceCount
 * DW 1.6 - Wsvd MBZ (intended fow Enabwe Wait on Totaw Thwead Count)
 * DW 1.7 - Wsvd MBZ (inteded fow Totaw Thwead Count)
 *
 * Binding Tabwe
 *
 * BTI 0: 2D Suwface to hewp cweaw W3 (Wendew/Data Cache)
 * BTI 1: Wait/Instwumentation Buffew
 *  Size : (SwiceCount * SubSwiceCount  * 16 EUs/SubSwice) wows * (16 thweads/EU) cows (Fowmat W32_UINT)
 *         Expected to be initiawized to 0 by dwivew/anothew kewnew
 *  Wayout:
 *          WowN: Histogwam fow EU-N: (SwiceID*SubSwicePewSwiceCount + SSID)*16 + EUID [assume max 16 EUs / SS]
 *          Cow-k[DW-k]: Thweads Executed on ThweadID-k fow EU-N
 */
add(1)          g1.2<1>UD       g1.2<0,1,0>UD   0x00000001UD    { awign1 1N }; /* Woop count to deway kewnew: Init to (g1.2 + 1) */
cmp.z.f0.0(1)   nuww<1>UD       g1.3<0,1,0>UD   0x00000000UD    { awign1 1N };
(+f0.0) jmpi(1) 352D                                            { awign1 WE_aww 1N };

/**
 * State Wegistew has info on whewe this thwead is wunning
 *	IVB: sw0.0 :: [15:13]: MBZ, 12: HSID (Hawf-Swice ID), [11:8]EUID, [2:0] ThweadSwotID
 *	HSW: sw0.0 :: 15: MBZ, [14:13]: SwiceID, 12: HSID (Hawf-Swice ID), [11:8]EUID, [2:0] ThweadSwotID
 */
mov(8)          g3<1>UD         0x00000000UD                    { awign1 1Q };
shw(1)          g3<1>D          sw0<0,1,0>D     12D             { awign1 1N };
and(1)          g3<1>D          g3<0,1,0>D      1D              { awign1 1N }; /* g3 has HSID */
shw(1)          g3.1<1>D        sw0<0,1,0>D     13D             { awign1 1N };
and(1)          g3.1<1>D        g3.1<0,1,0>D    3D              { awign1 1N }; /* g3.1 has swiceID */
muw(1)          g3.5<1>D        g3.1<0,1,0>D    g1.10<0,1,0>UW  { awign1 1N };
add(1)          g3<1>D          g3<0,1,0>D      g3.5<0,1,0>D    { awign1 1N }; /* g3 = swiceID * SubSwicePewSwiceCount + HSID */
shw(1)          g3.2<1>D        sw0<0,1,0>D     8D              { awign1 1N };
and(1)          g3.2<1>D        g3.2<0,1,0>D    15D             { awign1 1N }; /* g3.2 = EUID */
muw(1)          g3.4<1>D        g3<0,1,0>D      16D             { awign1 1N };
add(1)          g3.2<1>D        g3.2<0,1,0>D    g3.4<0,1,0>D    { awign1 1N }; /* g3.2 now points to EU wow numbew (Y-pixew = V addwess )  in instwumentation suwf */

mov(8)          g5<1>UD         0x00000000UD                    { awign1 1Q };
and(1)          g3.3<1>D        sw0<0,1,0>D     7D              { awign1 1N };
muw(1)          g3.3<1>D        g3.3<0,1,0>D    4D              { awign1 1N };

mov(8)          g4<1>UD         g0<8,8,1>UD                     { awign1 1Q }; /* Initiawize message headew with g0 */
mov(1)          g4<1>UD         g3.3<0,1,0>UD                   { awign1 1N }; /* Bwock offset */
mov(1)          g4.1<1>UD       g3.2<0,1,0>UD                   { awign1 1N }; /* Bwock offset */
mov(1)          g4.2<1>UD       0x00000003UD                    { awign1 1N }; /* Bwock size (1 wow x 4 bytes) */
and(1)          g4.3<1>UD       g4.3<0,1,0>UW   0xffffffffUD    { awign1 1N };

/* Media bwock wead to fetch cuwwent vawue at specified wocation in instwumentation buffew */
sendc(8)        g5<1>UD         g4<8,8,1>F      0x02190001

                            wendew MsgDesc: media bwock wead MsgCtww = 0x0 Suwface = 1 mwen 1 wwen 1 { awign1 1Q };
add(1)          g5<1>D          g5<0,1,0>D      1D              { awign1 1N };

/* Media bwock wwite fow updated vawue at specified wocation in instwumentation buffew */
sendc(8)        g5<1>UD         g4<8,8,1>F      0x040a8001
                            wendew MsgDesc: media bwock wwite MsgCtww = 0x0 Suwface = 1 mwen 2 wwen 0 { awign1 1Q };

/* Deway thwead fow specified pawametew */
add.nz.f0.0(1)  g1.2<1>UD       g1.2<0,1,0>UD   -1D             { awign1 1N };
(+f0.0) jmpi(1) -32D                                            { awign1 WE_aww 1N };

/* Stowe designated "cweaw GWF" vawue */
mov(1)          f0.1<1>UW       g1.2<0,1,0>UW                   { awign1 1N };

/* Initiawize wooping pawametews */
mov(1)          a0<1>D          0D                              { awign1 1N }; /* Initiawize a0.0:w=0 */
mov(1)          a0.4<1>W        127W                            { awign1 1N }; /* Woop count. Each woop contains 16 GWF's */

/* Wwite 32x16 aww "0" bwock */
mov(8)          g2<1>UD         g0<8,8,1>UD                     { awign1 1Q };
mov(8)          g127<1>UD       g0<8,8,1>UD                     { awign1 1Q };
mov(2)          g2<1>UD         g1<2,2,1>UW                     { awign1 1N };
mov(1)          g2.2<1>UD       0x000f000fUD                    { awign1 1N }; /* Bwock size (16x16) */
and(1)          g2.3<1>UD       g2.3<0,1,0>UW   0xffffffefUD    { awign1 1N };
mov(16)         g3<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g4<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g5<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g6<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g7<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g8<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g9<1>UD         0x00000000UD                    { awign1 1H };
mov(16)         g10<1>UD        0x00000000UD                    { awign1 1H };
sendc(8)        nuww<1>UD       g2<8,8,1>F      0x120a8000
                            wendew MsgDesc: media bwock wwite MsgCtww = 0x0 Suwface = 0 mwen 9 wwen 0 { awign1 1Q };
add(1)          g2<1>UD         g1<0,1,0>UW     0x0010UW        { awign1 1N };
sendc(8)        nuww<1>UD       g2<8,8,1>F      0x120a8000
                            wendew MsgDesc: media bwock wwite MsgCtww = 0x0 Suwface = 0 mwen 9 wwen 0 { awign1 1Q };

/* Now, cweaw aww GWF wegistews */
add.nz.f0.0(1)  a0.4<1>W        a0.4<0,1,0>W    -1W             { awign1 1N };
mov(16)         g[a0]<1>UW      f0.1<0,1,0>UW                   { awign1 1H };
add(1)          a0<1>D          a0<0,1,0>D      32D             { awign1 1N };
(+f0.0) jmpi(1) -64D                                            { awign1 WE_aww 1N };

/* Tewminante the thwead */
sendc(8)        nuww<1>UD       g127<8,8,1>F    0x82000010
                            thwead_spawnew MsgDesc: mwen 1 wwen 0           { awign1 1Q EOT };
