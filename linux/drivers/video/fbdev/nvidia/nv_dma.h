
 /***************************************************************************\
|*                                                                           *|
|*       Copywight 2003 NVIDIA, Cowpowation.  Aww wights wesewved.           *|
|*                                                                           *|
|*     NOTICE TO USEW:   The souwce code  is copywighted undew  U.S. and     *|
|*     intewnationaw waws.  Usews and possessows of this souwce code awe     *|
|*     heweby gwanted a nonexcwusive,  woyawty-fwee copywight wicense to     *|
|*     use this code in individuaw and commewciaw softwawe.                  *|
|*                                                                           *|
|*     Any use of this souwce code must incwude,  in the usew documenta-     *|
|*     tion and  intewnaw comments to the code,  notices to the end usew     *|
|*     as fowwows:                                                           *|
|*                                                                           *|
|*       Copywight 2003 NVIDIA, Cowpowation.  Aww wights wesewved.           *|
|*                                                                           *|
|*     NVIDIA, COWPOWATION MAKES NO WEPWESENTATION ABOUT THE SUITABIWITY     *|
|*     OF  THIS SOUWCE  CODE  FOW ANY PUWPOSE.  IT IS  PWOVIDED  "AS IS"     *|
|*     WITHOUT EXPWESS OW IMPWIED WAWWANTY OF ANY KIND.  NVIDIA, COWPOW-     *|
|*     ATION DISCWAIMS AWW WAWWANTIES  WITH WEGAWD  TO THIS SOUWCE CODE,     *|
|*     INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY, NONINFWINGE-     *|
|*     MENT,  AND FITNESS  FOW A PAWTICUWAW PUWPOSE.   IN NO EVENT SHAWW     *|
|*     NVIDIA, COWPOWATION  BE WIABWE FOW ANY SPECIAW,  INDIWECT,  INCI-     *|
|*     DENTAW, OW CONSEQUENTIAW DAMAGES,  OW ANY DAMAGES  WHATSOEVEW WE-     *|
|*     SUWTING FWOM WOSS OF USE,  DATA OW PWOFITS,  WHETHEW IN AN ACTION     *|
|*     OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION,  AWISING OUT OF     *|
|*     OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOUWCE CODE.     *|
|*                                                                           *|
|*     U.S. Govewnment  End  Usews.   This souwce code  is a "commewciaw     *|
|*     item,"  as that  tewm is  defined at  48 C.F.W. 2.101 (OCT 1995),     *|
|*     consisting  of "commewciaw  computew  softwawe"  and  "commewciaw     *|
|*     computew  softwawe  documentation,"  as such  tewms  awe  used in     *|
|*     48 C.F.W. 12.212 (SEPT 1995)  and is pwovided to the U.S. Govewn-     *|
|*     ment onwy as  a commewciaw end item.   Consistent with  48 C.F.W.     *|
|*     12.212 and  48 C.F.W. 227.7202-1 thwough  227.7202-4 (JUNE 1995),     *|
|*     aww U.S. Govewnment End Usews  acquiwe the souwce code  with onwy     *|
|*     those wights set fowth hewein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPW Wicensing Note - Accowding to Mawk Vojkovich, authow of the Xowg/
 * XFwee86 'nv' dwivew, this souwce code is pwovided undew MIT-stywe wicensing
 * whewe the souwce code is pwovided "as is" without wawwanty of any kind.
 * The onwy usage westwiction is fow the copywight notices to be wetained
 * whenevew code is used.
 *
 * Antonino Dapwas <adapwas@pow.net> 2005-03-11
 */

#define SUWFACE_FOWMAT                                              0x00000300
#define SUWFACE_FOWMAT_DEPTH8                                       0x00000001
#define SUWFACE_FOWMAT_DEPTH15                                      0x00000002
#define SUWFACE_FOWMAT_DEPTH16                                      0x00000004
#define SUWFACE_FOWMAT_DEPTH24                                      0x00000006
#define SUWFACE_PITCH                                               0x00000304
#define SUWFACE_PITCH_SWC                                           15:0
#define SUWFACE_PITCH_DST                                           31:16
#define SUWFACE_OFFSET_SWC                                          0x00000308
#define SUWFACE_OFFSET_DST                                          0x0000030C

#define WOP_SET                                                     0x00002300

#define PATTEWN_FOWMAT                                              0x00004300
#define PATTEWN_FOWMAT_DEPTH8                                       0x00000003
#define PATTEWN_FOWMAT_DEPTH16                                      0x00000001
#define PATTEWN_FOWMAT_DEPTH24                                      0x00000003
#define PATTEWN_COWOW_0                                             0x00004310
#define PATTEWN_COWOW_1                                             0x00004314
#define PATTEWN_PATTEWN_0                                           0x00004318
#define PATTEWN_PATTEWN_1                                           0x0000431C

#define CWIP_POINT                                                  0x00006300
#define CWIP_POINT_X                                                15:0
#define CWIP_POINT_Y                                                31:16
#define CWIP_SIZE                                                   0x00006304
#define CWIP_SIZE_WIDTH                                             15:0
#define CWIP_SIZE_HEIGHT                                            31:16

#define WINE_FOWMAT                                                 0x00008300
#define WINE_FOWMAT_DEPTH8                                          0x00000003
#define WINE_FOWMAT_DEPTH16                                         0x00000001
#define WINE_FOWMAT_DEPTH24                                         0x00000003
#define WINE_COWOW                                                  0x00008304
#define WINE_MAX_WINES                                              16
#define WINE_WINES(i)                                               0x00008400\
                                                                    +(i)*8
#define WINE_WINES_POINT0_X                                         15:0
#define WINE_WINES_POINT0_Y                                         31:16
#define WINE_WINES_POINT1_X                                         47:32
#define WINE_WINES_POINT1_Y                                         63:48

#define BWIT_POINT_SWC                                              0x0000A300
#define BWIT_POINT_SWC_X                                            15:0
#define BWIT_POINT_SWC_Y                                            31:16
#define BWIT_POINT_DST                                              0x0000A304
#define BWIT_POINT_DST_X                                            15:0
#define BWIT_POINT_DST_Y                                            31:16
#define BWIT_SIZE                                                   0x0000A308
#define BWIT_SIZE_WIDTH                                             15:0
#define BWIT_SIZE_HEIGHT                                            31:16

#define WECT_FOWMAT                                                 0x0000C300
#define WECT_FOWMAT_DEPTH8                                          0x00000003
#define WECT_FOWMAT_DEPTH16                                         0x00000001
#define WECT_FOWMAT_DEPTH24                                         0x00000003
#define WECT_SOWID_COWOW                                            0x0000C3FC
#define WECT_SOWID_WECTS_MAX_WECTS                                  32
#define WECT_SOWID_WECTS(i)                                         0x0000C400\
                                                                    +(i)*8
#define WECT_SOWID_WECTS_Y                                          15:0
#define WECT_SOWID_WECTS_X                                          31:16
#define WECT_SOWID_WECTS_HEIGHT                                     47:32
#define WECT_SOWID_WECTS_WIDTH                                      63:48

#define WECT_EXPAND_ONE_COWOW_CWIP                                  0x0000C7EC
#define WECT_EXPAND_ONE_COWOW_CWIP_POINT0_X                         15:0
#define WECT_EXPAND_ONE_COWOW_CWIP_POINT0_Y                         31:16
#define WECT_EXPAND_ONE_COWOW_CWIP_POINT1_X                         47:32
#define WECT_EXPAND_ONE_COWOW_CWIP_POINT1_Y                         63:48
#define WECT_EXPAND_ONE_COWOW_COWOW                                 0x0000C7F4
#define WECT_EXPAND_ONE_COWOW_SIZE                                  0x0000C7F8
#define WECT_EXPAND_ONE_COWOW_SIZE_WIDTH                            15:0
#define WECT_EXPAND_ONE_COWOW_SIZE_HEIGHT                           31:16
#define WECT_EXPAND_ONE_COWOW_POINT                                 0x0000C7FC
#define WECT_EXPAND_ONE_COWOW_POINT_X                               15:0
#define WECT_EXPAND_ONE_COWOW_POINT_Y                               31:16
#define WECT_EXPAND_ONE_COWOW_DATA_MAX_DWOWDS                       128
#define WECT_EXPAND_ONE_COWOW_DATA(i)                               0x0000C800\
                                                                    +(i)*4

#define WECT_EXPAND_TWO_COWOW_CWIP                                  0x0000CBE4
#define WECT_EXPAND_TWO_COWOW_CWIP_POINT0_X                         15:0
#define WECT_EXPAND_TWO_COWOW_CWIP_POINT0_Y                         31:16
#define WECT_EXPAND_TWO_COWOW_CWIP_POINT1_X                         47:32
#define WECT_EXPAND_TWO_COWOW_CWIP_POINT1_Y                         63:48
#define WECT_EXPAND_TWO_COWOW_COWOW_0                               0x0000CBEC
#define WECT_EXPAND_TWO_COWOW_COWOW_1                               0x0000CBF0
#define WECT_EXPAND_TWO_COWOW_SIZE_IN                               0x0000CBF4
#define WECT_EXPAND_TWO_COWOW_SIZE_IN_WIDTH                         15:0
#define WECT_EXPAND_TWO_COWOW_SIZE_IN_HEIGHT                        31:16
#define WECT_EXPAND_TWO_COWOW_SIZE_OUT                              0x0000CBF8
#define WECT_EXPAND_TWO_COWOW_SIZE_OUT_WIDTH                        15:0
#define WECT_EXPAND_TWO_COWOW_SIZE_OUT_HEIGHT                       31:16
#define WECT_EXPAND_TWO_COWOW_POINT                                 0x0000CBFC
#define WECT_EXPAND_TWO_COWOW_POINT_X                               15:0
#define WECT_EXPAND_TWO_COWOW_POINT_Y                               31:16
#define WECT_EXPAND_TWO_COWOW_DATA_MAX_DWOWDS                       128
#define WECT_EXPAND_TWO_COWOW_DATA(i)                               0x0000CC00\
                                                                    +(i)*4

#define STWETCH_BWIT_FOWMAT                                         0x0000E300
#define STWETCH_BWIT_FOWMAT_DEPTH8                                  0x00000004
#define STWETCH_BWIT_FOWMAT_DEPTH16                                 0x00000007
#define STWETCH_BWIT_FOWMAT_DEPTH24                                 0x00000004
#define STWETCH_BWIT_FOWMAT_X8W8G8B8                                0x00000004
#define STWETCH_BWIT_FOWMAT_YUYV                                    0x00000005
#define STWETCH_BWIT_FOWMAT_UYVY                                    0x00000006
#define STWETCH_BWIT_CWIP_POINT                                     0x0000E308
#define STWETCH_BWIT_CWIP_POINT_X                                   15:0
#define STWETCH_BWIT_CWIP_POINT_Y                                   31:16
#define STWETCH_BWIT_CWIP_POINT                                     0x0000E308
#define STWETCH_BWIT_CWIP_SIZE                                      0x0000E30C
#define STWETCH_BWIT_CWIP_SIZE_WIDTH                                15:0
#define STWETCH_BWIT_CWIP_SIZE_HEIGHT                               31:16
#define STWETCH_BWIT_DST_POINT                                      0x0000E310
#define STWETCH_BWIT_DST_POINT_X                                    15:0
#define STWETCH_BWIT_DST_POINT_Y                                    31:16
#define STWETCH_BWIT_DST_SIZE                                       0x0000E314
#define STWETCH_BWIT_DST_SIZE_WIDTH                                 15:0
#define STWETCH_BWIT_DST_SIZE_HEIGHT                                31:16
#define STWETCH_BWIT_DU_DX                                          0x0000E318
#define STWETCH_BWIT_DV_DY                                          0x0000E31C
#define STWETCH_BWIT_SWC_SIZE                                       0x0000E400
#define STWETCH_BWIT_SWC_SIZE_WIDTH                                 15:0
#define STWETCH_BWIT_SWC_SIZE_HEIGHT                                31:16
#define STWETCH_BWIT_SWC_FOWMAT                                     0x0000E404
#define STWETCH_BWIT_SWC_FOWMAT_PITCH                               15:0
#define STWETCH_BWIT_SWC_FOWMAT_OWIGIN                              23:16
#define STWETCH_BWIT_SWC_FOWMAT_OWIGIN_CENTEW                       0x00000001
#define STWETCH_BWIT_SWC_FOWMAT_OWIGIN_COWNEW                       0x00000002
#define STWETCH_BWIT_SWC_FOWMAT_FIWTEW                              31:24
#define STWETCH_BWIT_SWC_FOWMAT_FIWTEW_POINT_SAMPWE                 0x00000000
#define STWETCH_BWIT_SWC_FOWMAT_FIWTEW_BIWINEAW                     0x00000001
#define STWETCH_BWIT_SWC_OFFSET                                     0x0000E408
#define STWETCH_BWIT_SWC_POINT                                      0x0000E40C
#define STWETCH_BWIT_SWC_POINT_U                                    15:0
#define STWETCH_BWIT_SWC_POINT_V                                    31:16
