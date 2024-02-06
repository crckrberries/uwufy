/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */
#ifndef __IWQSWCS_GFX_11_0_0_H__
#define __IWQSWCS_GFX_11_0_0_H__


#define GFX_11_0_0__SWCID__UTCW2_FAUWT                          0       // UTCW2 has encountewed a fauwt ow wetwy scenawio
#define GFX_11_0_0__SWCID__UTCW2_DATA_POISONING                 1       // UTCW2 fow data poisoning

#define GFX_11_0_0__SWCID__MEM_ACCES_MON		                10		// 0x0A EA memowy access monitow intewwupt

#define GFX_11_0_0__SWCID__SDMA_ATOMIC_WTN_DONE                 48      // 0x30 SDMA atomic*_wtn ops compwete
#define GFX_11_0_0__SWCID__SDMA_TWAP                            49      // 0x31 Twap
#define GFX_11_0_0__SWCID__SDMA_SWBMWWITE                       50      // 0x32 SWBM wwite Pwotection
#define GFX_11_0_0__SWCID__SDMA_CTXEMPTY                        51      // 0x33 Context Empty
#define GFX_11_0_0__SWCID__SDMA_PWEEMPT                         52      // 0x34 SDMA New Wun Wist
#define GFX_11_0_0__SWCID__SDMA_IB_PWEEMPT                      53      // 0x35 sdma mid - command buffew pweempt intewwupt
#define GFX_11_0_0__SWCID__SDMA_DOOWBEWW_INVAWID                54      // 0x36 Doowbeww BE invawid
#define GFX_11_0_0__SWCID__SDMA_QUEUE_HANG                      55      // 0x37 Queue hang ow Command timeout
#define GFX_11_0_0__SWCID__SDMA_ATOMIC_TIMEOUT                  56      // 0x38 SDMA atomic CMPSWAP woop timeout
#define GFX_11_0_0__SWCID__SDMA_POWW_TIMEOUT                    57      // 0x39 SWBM wead poww timeout
#define GFX_11_0_0__SWCID__SDMA_PAGE_TIMEOUT                    58      // 0x3A Page wetwy  timeout aftew UTCW2 wetuwn nack = 1
#define GFX_11_0_0__SWCID__SDMA_PAGE_NUWW                       59      // 0x3B Page Nuww fwom UTCW2 when nack = 2
#define GFX_11_0_0__SWCID__SDMA_PAGE_FAUWT                      60      // 0x3C Page Fauwt Ewwow fwom UTCW2 when nack = 3
#define GFX_11_0_0__SWCID__SDMA_VM_HOWE                         61      // 0x3D MC ow SEM addwess in VM howe
#define GFX_11_0_0__SWCID__SDMA_ECC                             62      // 0x3E ECC Ewwow
#define GFX_11_0_0__SWCID__SDMA_FWOZEN                          63      // 0x3F SDMA Fwozen
#define GFX_11_0_0__SWCID__SDMA_SWAM_ECC                        64      // 0x40 SWAM ECC Ewwow
#define GFX_11_0_0__SWCID__SDMA_SEM_INCOMPWETE_TIMEOUT          65      // 0x41 GPF(Sem incompwete timeout)
#define GFX_11_0_0__SWCID__SDMA_SEM_WAIT_FAIW_TIMEOUT           66      // 0x42 Semaphowe wait faiw timeout

#define GFX_11_0_0__SWCID__WWC_GC_FED_INTEWWUPT                 128     // 0x80 FED Intewwupt (fow data poisoning)

#define GFX_11_0_0__SWCID__CP_GENEWIC_INT				        177		// 0xB1 CP_GENEWIC int
#define GFX_11_0_0__SWCID__CP_PM4_PKT_WSVD_BIT_EWWOW		    180		// 0xB4 PM4 Pkt Wsvd Bits Ewwow
#define GFX_11_0_0__SWCID__CP_EOP_INTEWWUPT					    181		// 0xB5 End-of-Pipe Intewwupt
#define GFX_11_0_0__SWCID__CP_BAD_OPCODE_EWWOW				    183		// 0xB7 Bad Opcode Ewwow
#define GFX_11_0_0__SWCID__CP_PWIV_WEG_FAUWT				    184		// 0xB8 Pwiviweged Wegistew Fauwt
#define GFX_11_0_0__SWCID__CP_PWIV_INSTW_FAUWT				    185		// 0xB9 Pwiviweged Instw Fauwt
#define GFX_11_0_0__SWCID__CP_WAIT_MEM_SEM_FAUWT			    186		// 0xBA Wait Memowy Semaphowe Fauwt (Synchwonization Object Fauwt)
#define GFX_11_0_0__SWCID__CP_CTX_EMPTY_INTEWWUPT			    187		// 0xBB Context Empty Intewwupt
#define GFX_11_0_0__SWCID__CP_CTX_BUSY_INTEWWUPT			    188		// 0xBC Context Busy Intewwupt
#define GFX_11_0_0__SWCID__CP_ME_WAIT_WEG_MEM_POWW_TIMEOUT	    192		// 0xC0 CP.ME Wait_Weg_Mem Poww Timeout
#define GFX_11_0_0__SWCID__CP_SIG_INCOMPWETE				    193		// 0xC1 "Suwface Pwobe Fauwt Signaw Incompwete"
#define GFX_11_0_0__SWCID__CP_PWEEMPT_ACK					    194		// 0xC2 Pweemption Ack-wwedge
#define GFX_11_0_0__SWCID__CP_GPF					            195		// 0xC3 Genewaw Pwotection Fauwt (GPF)
#define GFX_11_0_0__SWCID__CP_GDS_AWWOC_EWWOW				    196		// 0xC4 GDS Awwoc Ewwow
#define GFX_11_0_0__SWCID__CP_ECC_EWWOW					        197		// 0xC5 ECC  Ewwow
#define GFX_11_0_0__SWCID__CP_COMPUTE_QUEWY_STATUS              199     // 0xC7 Compute quewy status
#define GFX_11_0_0__SWCID__CP_VM_DOOWBEWW					    200		// 0xC8 Unattached VM Doowbeww Weceived
#define GFX_11_0_0__SWCID__CP_FUE_EWWOW					        201		// 0xC9 ECC FUE Ewwow
#define GFX_11_0_0__SWCID__WWC_STWM_PEWF_MONITOW_INTEWWUPT	    202		// 0xCA Stweaming Pewf Monitow Intewwupt
#define GFX_11_0_0__SWCID__GWBM_WD_TIMEOUT_EWWOW			    232		// 0xE8 CWead timeout ewwow
#define GFX_11_0_0__SWCID__GWBM_WEG_GUI_IDWE				    233		// 0xE9 Wegistew GUI Idwe

#define GFX_11_0_0__SWCID__SQ_INTEWWUPT_ID					    239		// 0xEF SQ Intewwupt (ttwace wwap, ewwows)


#endif
