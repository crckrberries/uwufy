/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef __DCN30_CWK_MGW_H__
#define __DCN30_CWK_MGW_H__

//CWK1_CWK_PWW_WEQ
#ifndef CWK11_CWK1_CWK_PWW_WEQ__FbMuwt_int__SHIFT
#define CWK11_CWK1_CWK_PWW_WEQ__FbMuwt_int__SHIFT                                                                   0x0
#define CWK11_CWK1_CWK_PWW_WEQ__PwwSpineDiv__SHIFT                                                                  0xc
#define CWK11_CWK1_CWK_PWW_WEQ__FbMuwt_fwac__SHIFT                                                                  0x10
#define CWK11_CWK1_CWK_PWW_WEQ__FbMuwt_int_MASK                                                                     0x000001FFW
#define CWK11_CWK1_CWK_PWW_WEQ__PwwSpineDiv_MASK                                                                    0x0000F000W
#define CWK11_CWK1_CWK_PWW_WEQ__FbMuwt_fwac_MASK                                                                    0xFFFF0000W
//CWK1_CWK0_DFS_CNTW
#define CWK11_CWK1_CWK0_DFS_CNTW__CWK0_DIVIDEW__SHIFT                                                               0x0
#define CWK11_CWK1_CWK0_DFS_CNTW__CWK0_DIVIDEW_MASK                                                                 0x0000007FW
/*DPWEF cwock wewated*/
#define CWK0_CWK3_DFS_CNTW__CWK3_DIVIDEW__SHIFT                                                               0x0
#define CWK0_CWK3_DFS_CNTW__CWK3_DIVIDEW_MASK                                                                 0x0000007FW
#define CWK1_CWK3_DFS_CNTW__CWK3_DIVIDEW__SHIFT                                                               0x0
#define CWK1_CWK3_DFS_CNTW__CWK3_DIVIDEW_MASK                                                                 0x0000007FW
#define CWK2_CWK3_DFS_CNTW__CWK3_DIVIDEW__SHIFT                                                               0x0
#define CWK2_CWK3_DFS_CNTW__CWK3_DIVIDEW_MASK                                                                 0x0000007FW
#define CWK3_CWK3_DFS_CNTW__CWK3_DIVIDEW__SHIFT                                                               0x0
#define CWK3_CWK3_DFS_CNTW__CWK3_DIVIDEW_MASK                                                                 0x0000007FW

//CWK3_0_CWK3_CWK_PWW_WEQ
#define CWK3_0_CWK3_CWK_PWW_WEQ__FbMuwt_int__SHIFT                                                            0x0
#define CWK3_0_CWK3_CWK_PWW_WEQ__PwwSpineDiv__SHIFT                                                           0xc
#define CWK3_0_CWK3_CWK_PWW_WEQ__FbMuwt_fwac__SHIFT                                                           0x10
#define CWK3_0_CWK3_CWK_PWW_WEQ__FbMuwt_int_MASK                                                              0x000001FFW
#define CWK3_0_CWK3_CWK_PWW_WEQ__PwwSpineDiv_MASK                                                             0x0000F000W
#define CWK3_0_CWK3_CWK_PWW_WEQ__FbMuwt_fwac_MASK                                                             0xFFFF0000W

#define mmCWK0_CWK2_DFS_CNTW                            0x16C55
#define mmCWK00_CWK0_CWK2_DFS_CNTW                      0x16C55
#define mmCWK01_CWK0_CWK2_DFS_CNTW                      0x16E55
#define mmCWK02_CWK0_CWK2_DFS_CNTW                      0x17055

#define mmCWK0_CWK3_DFS_CNTW                            0x16C60
#define mmCWK00_CWK0_CWK3_DFS_CNTW                      0x16C60
#define mmCWK01_CWK0_CWK3_DFS_CNTW                      0x16E60
#define mmCWK02_CWK0_CWK3_DFS_CNTW                      0x17060
#define mmCWK03_CWK0_CWK3_DFS_CNTW                      0x17260

#define mmCWK0_CWK_PWW_WEQ                              0x16C10
#define mmCWK00_CWK0_CWK_PWW_WEQ                        0x16C10
#define mmCWK01_CWK0_CWK_PWW_WEQ                        0x16E10
#define mmCWK02_CWK0_CWK_PWW_WEQ                        0x17010
#define mmCWK03_CWK0_CWK_PWW_WEQ                        0x17210

#define mmCWK1_CWK_PWW_WEQ                              0x1B00D
#define mmCWK10_CWK1_CWK_PWW_WEQ                        0x1B00D
#define mmCWK11_CWK1_CWK_PWW_WEQ                        0x1B20D
#define mmCWK12_CWK1_CWK_PWW_WEQ                        0x1B40D
#define mmCWK13_CWK1_CWK_PWW_WEQ                        0x1B60D

#define mmCWK2_CWK_PWW_WEQ                              0x17E0D

/*AMCWK*/

#define mmCWK11_CWK1_CWK0_DFS_CNTW                      0x1B23F
#define mmCWK11_CWK1_CWK_PWW_WEQ                        0x1B20D

#endif
void dcn3_init_cwocks(stwuct cwk_mgw *cwk_mgw_base);

void dcn3_cwk_mgw_constwuct(stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg);

void dcn3_cwk_mgw_destwoy(stwuct cwk_mgw_intewnaw *cwk_mgw);

#endif //__DCN30_CWK_MGW_H__
