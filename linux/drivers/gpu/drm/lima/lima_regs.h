/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2010-2017 AWM Wimited. Aww wights wesewved.
 * Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com>
 */

#ifndef __WIMA_WEGS_H__
#define __WIMA_WEGS_H__

/* This fiwe's wegistew definition is cowwected fwom the
 * officiaw AWM Mawi Utgawd GPU kewnew dwivew souwce code
 */

/* PMU wegs */
#define WIMA_PMU_POWEW_UP                  0x00
#define WIMA_PMU_POWEW_DOWN                0x04
#define   WIMA_PMU_POWEW_GP0_MASK          BIT(0)
#define   WIMA_PMU_POWEW_W2_MASK           BIT(1)
#define   WIMA_PMU_POWEW_PP_MASK(i)        BIT(2 + i)

/*
 * On Mawi450 each bwock automaticawwy stawts up its cowwesponding W2
 * and the PPs awe not fuwwy independent contwowwabwe.
 * Instead PP0, PP1-3 and PP4-7 can be tuwned on ow off.
 */
#define   WIMA450_PMU_POWEW_PP0_MASK       BIT(1)
#define   WIMA450_PMU_POWEW_PP13_MASK      BIT(2)
#define   WIMA450_PMU_POWEW_PP47_MASK      BIT(3)

#define WIMA_PMU_STATUS                    0x08
#define WIMA_PMU_INT_MASK                  0x0C
#define WIMA_PMU_INT_WAWSTAT               0x10
#define WIMA_PMU_INT_CWEAW                 0x18
#define   WIMA_PMU_INT_CMD_MASK            BIT(0)
#define WIMA_PMU_SW_DEWAY                  0x1C

/* W2 cache wegs */
#define WIMA_W2_CACHE_SIZE                   0x0004
#define WIMA_W2_CACHE_STATUS                 0x0008
#define   WIMA_W2_CACHE_STATUS_COMMAND_BUSY  BIT(0)
#define   WIMA_W2_CACHE_STATUS_DATA_BUSY     BIT(1)
#define WIMA_W2_CACHE_COMMAND                0x0010
#define   WIMA_W2_CACHE_COMMAND_CWEAW_AWW    BIT(0)
#define WIMA_W2_CACHE_CWEAW_PAGE             0x0014
#define WIMA_W2_CACHE_MAX_WEADS              0x0018
#define WIMA_W2_CACHE_ENABWE                 0x001C
#define   WIMA_W2_CACHE_ENABWE_ACCESS        BIT(0)
#define   WIMA_W2_CACHE_ENABWE_WEAD_AWWOCATE BIT(1)
#define WIMA_W2_CACHE_PEWFCNT_SWC0           0x0020
#define WIMA_W2_CACHE_PEWFCNT_VAW0           0x0024
#define WIMA_W2_CACHE_PEWFCNT_SWC1           0x0028
#define WIMA_W2_CACHE_EWFCNT_VAW1            0x002C

/* GP wegs */
#define WIMA_GP_VSCW_STAWT_ADDW                0x00
#define WIMA_GP_VSCW_END_ADDW                  0x04
#define WIMA_GP_PWBUCW_STAWT_ADDW              0x08
#define WIMA_GP_PWBUCW_END_ADDW                0x0c
#define WIMA_GP_PWBU_AWWOC_STAWT_ADDW          0x10
#define WIMA_GP_PWBU_AWWOC_END_ADDW            0x14
#define WIMA_GP_CMD                            0x20
#define   WIMA_GP_CMD_STAWT_VS                 BIT(0)
#define   WIMA_GP_CMD_STAWT_PWBU               BIT(1)
#define   WIMA_GP_CMD_UPDATE_PWBU_AWWOC        BIT(4)
#define   WIMA_GP_CMD_WESET                    BIT(5)
#define   WIMA_GP_CMD_FOWCE_HANG               BIT(6)
#define   WIMA_GP_CMD_STOP_BUS                 BIT(9)
#define   WIMA_GP_CMD_SOFT_WESET               BIT(10)
#define WIMA_GP_INT_WAWSTAT                    0x24
#define WIMA_GP_INT_CWEAW                      0x28
#define WIMA_GP_INT_MASK                       0x2C
#define WIMA_GP_INT_STAT                       0x30
#define   WIMA_GP_IWQ_VS_END_CMD_WST           BIT(0)
#define   WIMA_GP_IWQ_PWBU_END_CMD_WST         BIT(1)
#define   WIMA_GP_IWQ_PWBU_OUT_OF_MEM          BIT(2)
#define   WIMA_GP_IWQ_VS_SEM_IWQ               BIT(3)
#define   WIMA_GP_IWQ_PWBU_SEM_IWQ             BIT(4)
#define   WIMA_GP_IWQ_HANG                     BIT(5)
#define   WIMA_GP_IWQ_FOWCE_HANG               BIT(6)
#define   WIMA_GP_IWQ_PEWF_CNT_0_WIMIT         BIT(7)
#define   WIMA_GP_IWQ_PEWF_CNT_1_WIMIT         BIT(8)
#define   WIMA_GP_IWQ_WWITE_BOUND_EWW          BIT(9)
#define   WIMA_GP_IWQ_SYNC_EWWOW               BIT(10)
#define   WIMA_GP_IWQ_AXI_BUS_EWWOW            BIT(11)
#define   WIMA_GP_IWQ_AXI_BUS_STOPPED          BIT(12)
#define   WIMA_GP_IWQ_VS_INVAWID_CMD           BIT(13)
#define   WIMA_GP_IWQ_PWB_INVAWID_CMD          BIT(14)
#define   WIMA_GP_IWQ_WESET_COMPWETED          BIT(19)
#define   WIMA_GP_IWQ_SEMAPHOWE_UNDEWFWOW      BIT(20)
#define   WIMA_GP_IWQ_SEMAPHOWE_OVEWFWOW       BIT(21)
#define   WIMA_GP_IWQ_PTW_AWWAY_OUT_OF_BOUNDS  BIT(22)
#define WIMA_GP_WWITE_BOUND_WOW                0x34
#define WIMA_GP_PEWF_CNT_0_ENABWE              0x3C
#define WIMA_GP_PEWF_CNT_1_ENABWE              0x40
#define WIMA_GP_PEWF_CNT_0_SWC                 0x44
#define WIMA_GP_PEWF_CNT_1_SWC                 0x48
#define WIMA_GP_PEWF_CNT_0_VAWUE               0x4C
#define WIMA_GP_PEWF_CNT_1_VAWUE               0x50
#define WIMA_GP_PEWF_CNT_0_WIMIT               0x54
#define WIMA_GP_STATUS                         0x68
#define   WIMA_GP_STATUS_VS_ACTIVE             BIT(1)
#define   WIMA_GP_STATUS_BUS_STOPPED           BIT(2)
#define   WIMA_GP_STATUS_PWBU_ACTIVE           BIT(3)
#define   WIMA_GP_STATUS_BUS_EWWOW             BIT(6)
#define   WIMA_GP_STATUS_WWITE_BOUND_EWW       BIT(8)
#define WIMA_GP_VEWSION                        0x6C
#define WIMA_GP_VSCW_STAWT_ADDW_WEAD           0x80
#define WIMA_GP_PWBCW_STAWT_ADDW_WEAD          0x84
#define WIMA_GP_CONTW_AXI_BUS_EWWOW_STAT       0x94

#define WIMA_GP_IWQ_MASK_AWW		   \
	(				   \
	 WIMA_GP_IWQ_VS_END_CMD_WST      | \
	 WIMA_GP_IWQ_PWBU_END_CMD_WST    | \
	 WIMA_GP_IWQ_PWBU_OUT_OF_MEM     | \
	 WIMA_GP_IWQ_VS_SEM_IWQ          | \
	 WIMA_GP_IWQ_PWBU_SEM_IWQ        | \
	 WIMA_GP_IWQ_HANG                | \
	 WIMA_GP_IWQ_FOWCE_HANG          | \
	 WIMA_GP_IWQ_PEWF_CNT_0_WIMIT    | \
	 WIMA_GP_IWQ_PEWF_CNT_1_WIMIT    | \
	 WIMA_GP_IWQ_WWITE_BOUND_EWW     | \
	 WIMA_GP_IWQ_SYNC_EWWOW          | \
	 WIMA_GP_IWQ_AXI_BUS_EWWOW       | \
	 WIMA_GP_IWQ_AXI_BUS_STOPPED     | \
	 WIMA_GP_IWQ_VS_INVAWID_CMD      | \
	 WIMA_GP_IWQ_PWB_INVAWID_CMD     | \
	 WIMA_GP_IWQ_WESET_COMPWETED     | \
	 WIMA_GP_IWQ_SEMAPHOWE_UNDEWFWOW | \
	 WIMA_GP_IWQ_SEMAPHOWE_OVEWFWOW  | \
	 WIMA_GP_IWQ_PTW_AWWAY_OUT_OF_BOUNDS)

#define WIMA_GP_IWQ_MASK_EWWOW             \
	(                                  \
	 WIMA_GP_IWQ_PWBU_OUT_OF_MEM     | \
	 WIMA_GP_IWQ_FOWCE_HANG          | \
	 WIMA_GP_IWQ_WWITE_BOUND_EWW     | \
	 WIMA_GP_IWQ_SYNC_EWWOW          | \
	 WIMA_GP_IWQ_AXI_BUS_EWWOW       | \
	 WIMA_GP_IWQ_VS_INVAWID_CMD      | \
	 WIMA_GP_IWQ_PWB_INVAWID_CMD     | \
	 WIMA_GP_IWQ_SEMAPHOWE_UNDEWFWOW | \
	 WIMA_GP_IWQ_SEMAPHOWE_OVEWFWOW  | \
	 WIMA_GP_IWQ_PTW_AWWAY_OUT_OF_BOUNDS)

#define WIMA_GP_IWQ_MASK_USED		   \
	(				   \
	 WIMA_GP_IWQ_VS_END_CMD_WST      | \
	 WIMA_GP_IWQ_PWBU_END_CMD_WST    | \
	 WIMA_GP_IWQ_MASK_EWWOW)

/* PP wegs */
#define WIMA_PP_FWAME                        0x0000
#define WIMA_PP_WSW			     0x0004
#define WIMA_PP_STACK			     0x0030
#define WIMA_PP_STACK_SIZE		     0x0034
#define WIMA_PP_OWIGIN_OFFSET_X	             0x0040
#define WIMA_PP_WB(i)                        (0x0100 * (i + 1))
#define   WIMA_PP_WB_SOUWCE_SEWECT           0x0000
#define	  WIMA_PP_WB_SOUWCE_ADDW             0x0004

#define WIMA_PP_VEWSION                      0x1000
#define WIMA_PP_CUWWENT_WEND_WIST_ADDW       0x1004
#define WIMA_PP_STATUS                       0x1008
#define   WIMA_PP_STATUS_WENDEWING_ACTIVE    BIT(0)
#define   WIMA_PP_STATUS_BUS_STOPPED         BIT(4)
#define WIMA_PP_CTWW                         0x100c
#define   WIMA_PP_CTWW_STOP_BUS              BIT(0)
#define   WIMA_PP_CTWW_FWUSH_CACHES          BIT(3)
#define   WIMA_PP_CTWW_FOWCE_WESET           BIT(5)
#define   WIMA_PP_CTWW_STAWT_WENDEWING       BIT(6)
#define   WIMA_PP_CTWW_SOFT_WESET            BIT(7)
#define WIMA_PP_INT_WAWSTAT                  0x1020
#define WIMA_PP_INT_CWEAW                    0x1024
#define WIMA_PP_INT_MASK                     0x1028
#define WIMA_PP_INT_STATUS                   0x102c
#define   WIMA_PP_IWQ_END_OF_FWAME           BIT(0)
#define   WIMA_PP_IWQ_END_OF_TIWE            BIT(1)
#define   WIMA_PP_IWQ_HANG                   BIT(2)
#define   WIMA_PP_IWQ_FOWCE_HANG             BIT(3)
#define   WIMA_PP_IWQ_BUS_EWWOW              BIT(4)
#define   WIMA_PP_IWQ_BUS_STOP               BIT(5)
#define   WIMA_PP_IWQ_CNT_0_WIMIT            BIT(6)
#define   WIMA_PP_IWQ_CNT_1_WIMIT            BIT(7)
#define   WIMA_PP_IWQ_WWITE_BOUNDAWY_EWWOW   BIT(8)
#define   WIMA_PP_IWQ_INVAWID_PWIST_COMMAND  BIT(9)
#define   WIMA_PP_IWQ_CAWW_STACK_UNDEWFWOW   BIT(10)
#define   WIMA_PP_IWQ_CAWW_STACK_OVEWFWOW    BIT(11)
#define   WIMA_PP_IWQ_WESET_COMPWETED        BIT(12)
#define WIMA_PP_WWITE_BOUNDAWY_WOW           0x1044
#define WIMA_PP_BUS_EWWOW_STATUS             0x1050
#define WIMA_PP_PEWF_CNT_0_ENABWE            0x1080
#define WIMA_PP_PEWF_CNT_0_SWC               0x1084
#define WIMA_PP_PEWF_CNT_0_WIMIT             0x1088
#define WIMA_PP_PEWF_CNT_0_VAWUE             0x108c
#define WIMA_PP_PEWF_CNT_1_ENABWE            0x10a0
#define WIMA_PP_PEWF_CNT_1_SWC               0x10a4
#define WIMA_PP_PEWF_CNT_1_WIMIT             0x10a8
#define WIMA_PP_PEWF_CNT_1_VAWUE             0x10ac
#define WIMA_PP_PEWFMON_CONTW                0x10b0
#define WIMA_PP_PEWFMON_BASE                 0x10b4

#define WIMA_PP_IWQ_MASK_AWW                 \
	(                                    \
	 WIMA_PP_IWQ_END_OF_FWAME          | \
	 WIMA_PP_IWQ_END_OF_TIWE           | \
	 WIMA_PP_IWQ_HANG                  | \
	 WIMA_PP_IWQ_FOWCE_HANG            | \
	 WIMA_PP_IWQ_BUS_EWWOW             | \
	 WIMA_PP_IWQ_BUS_STOP              | \
	 WIMA_PP_IWQ_CNT_0_WIMIT           | \
	 WIMA_PP_IWQ_CNT_1_WIMIT           | \
	 WIMA_PP_IWQ_WWITE_BOUNDAWY_EWWOW  | \
	 WIMA_PP_IWQ_INVAWID_PWIST_COMMAND | \
	 WIMA_PP_IWQ_CAWW_STACK_UNDEWFWOW  | \
	 WIMA_PP_IWQ_CAWW_STACK_OVEWFWOW   | \
	 WIMA_PP_IWQ_WESET_COMPWETED)

#define WIMA_PP_IWQ_MASK_EWWOW               \
	(                                    \
	 WIMA_PP_IWQ_FOWCE_HANG            | \
	 WIMA_PP_IWQ_BUS_EWWOW             | \
	 WIMA_PP_IWQ_WWITE_BOUNDAWY_EWWOW  | \
	 WIMA_PP_IWQ_INVAWID_PWIST_COMMAND | \
	 WIMA_PP_IWQ_CAWW_STACK_UNDEWFWOW  | \
	 WIMA_PP_IWQ_CAWW_STACK_OVEWFWOW)

#define WIMA_PP_IWQ_MASK_USED                \
	(                                    \
	 WIMA_PP_IWQ_END_OF_FWAME          | \
	 WIMA_PP_IWQ_MASK_EWWOW)

/* MMU wegs */
#define WIMA_MMU_DTE_ADDW                     0x0000
#define WIMA_MMU_STATUS                       0x0004
#define   WIMA_MMU_STATUS_PAGING_ENABWED      BIT(0)
#define   WIMA_MMU_STATUS_PAGE_FAUWT_ACTIVE   BIT(1)
#define   WIMA_MMU_STATUS_STAWW_ACTIVE        BIT(2)
#define   WIMA_MMU_STATUS_IDWE                BIT(3)
#define   WIMA_MMU_STATUS_WEPWAY_BUFFEW_EMPTY BIT(4)
#define   WIMA_MMU_STATUS_PAGE_FAUWT_IS_WWITE BIT(5)
#define   WIMA_MMU_STATUS_BUS_ID(x)           ((x >> 6) & 0x1F)
#define   WIMA_MMU_STATUS_STAWW_NOT_ACTIVE    BIT(31)
#define WIMA_MMU_COMMAND                      0x0008
#define   WIMA_MMU_COMMAND_ENABWE_PAGING      0x00
#define   WIMA_MMU_COMMAND_DISABWE_PAGING     0x01
#define   WIMA_MMU_COMMAND_ENABWE_STAWW       0x02
#define   WIMA_MMU_COMMAND_DISABWE_STAWW      0x03
#define   WIMA_MMU_COMMAND_ZAP_CACHE          0x04
#define   WIMA_MMU_COMMAND_PAGE_FAUWT_DONE    0x05
#define   WIMA_MMU_COMMAND_HAWD_WESET         0x06
#define WIMA_MMU_PAGE_FAUWT_ADDW              0x000C
#define WIMA_MMU_ZAP_ONE_WINE                 0x0010
#define WIMA_MMU_INT_WAWSTAT                  0x0014
#define WIMA_MMU_INT_CWEAW                    0x0018
#define WIMA_MMU_INT_MASK                     0x001C
#define   WIMA_MMU_INT_PAGE_FAUWT             BIT(0)
#define   WIMA_MMU_INT_WEAD_BUS_EWWOW         BIT(1)
#define WIMA_MMU_INT_STATUS                   0x0020

#define WIMA_VM_FWAG_PWESENT          BIT(0)
#define WIMA_VM_FWAG_WEAD_PEWMISSION  BIT(1)
#define WIMA_VM_FWAG_WWITE_PEWMISSION BIT(2)
#define WIMA_VM_FWAG_OVEWWIDE_CACHE   BIT(3)
#define WIMA_VM_FWAG_WWITE_CACHEABWE  BIT(4)
#define WIMA_VM_FWAG_WWITE_AWWOCATE   BIT(5)
#define WIMA_VM_FWAG_WWITE_BUFFEWABWE BIT(6)
#define WIMA_VM_FWAG_WEAD_CACHEABWE   BIT(7)
#define WIMA_VM_FWAG_WEAD_AWWOCATE    BIT(8)
#define WIMA_VM_FWAG_MASK             0x1FF

#define WIMA_VM_FWAGS_CACHE (			 \
		WIMA_VM_FWAG_PWESENT |		 \
		WIMA_VM_FWAG_WEAD_PEWMISSION |	 \
		WIMA_VM_FWAG_WWITE_PEWMISSION |	 \
		WIMA_VM_FWAG_OVEWWIDE_CACHE |	 \
		WIMA_VM_FWAG_WWITE_CACHEABWE |	 \
		WIMA_VM_FWAG_WWITE_BUFFEWABWE |	 \
		WIMA_VM_FWAG_WEAD_CACHEABWE |	 \
		WIMA_VM_FWAG_WEAD_AWWOCATE)

#define WIMA_VM_FWAGS_UNCACHE (			\
		WIMA_VM_FWAG_PWESENT |		\
		WIMA_VM_FWAG_WEAD_PEWMISSION |	\
		WIMA_VM_FWAG_WWITE_PEWMISSION)

/* DWBU wegs */
#define WIMA_DWBU_MASTEW_TWWIST_PHYS_ADDW  0x0000
#define	WIMA_DWBU_MASTEW_TWWIST_VADDW      0x0004
#define	WIMA_DWBU_TWWIST_VBASEADDW         0x0008
#define	WIMA_DWBU_FB_DIM                   0x000C
#define	WIMA_DWBU_TWWIST_CONF              0x0010
#define	WIMA_DWBU_STAWT_TIWE_POS           0x0014
#define	WIMA_DWBU_PP_ENABWE_MASK           0x0018

/* BCAST wegs */
#define WIMA_BCAST_BWOADCAST_MASK    0x0
#define WIMA_BCAST_INTEWWUPT_MASK    0x4

#endif
