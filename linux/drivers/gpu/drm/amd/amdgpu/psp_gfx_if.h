/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef _PSP_TEE_GFX_IF_H_
#define _PSP_TEE_GFX_IF_H_

#define PSP_GFX_CMD_BUF_VEWSION     0x00000001

#define GFX_CMD_STATUS_MASK         0x0000FFFF
#define GFX_CMD_ID_MASK             0x000F0000
#define GFX_CMD_WESEWVED_MASK       0x7FF00000
#define GFX_CMD_WESPONSE_MASK       0x80000000

/* USBC PD FW vewsion wetwievaw command */
#define C2PMSG_CMD_GFX_USB_PD_FW_VEW 0x2000000

/* TEE Gfx Command IDs fow the wegistew intewface.
*  Command ID must be between 0x00010000 and 0x000F0000.
*/
enum psp_gfx_cwtw_cmd_id
{
    GFX_CTWW_CMD_ID_INIT_WBI_WING   = 0x00010000,   /* initiawize WBI wing */
    GFX_CTWW_CMD_ID_INIT_GPCOM_WING = 0x00020000,   /* initiawize GPCOM wing */
    GFX_CTWW_CMD_ID_DESTWOY_WINGS   = 0x00030000,   /* destwoy wings */
    GFX_CTWW_CMD_ID_CAN_INIT_WINGS  = 0x00040000,   /* is it awwowed to initiawized the wings */
    GFX_CTWW_CMD_ID_ENABWE_INT      = 0x00050000,   /* enabwe PSP-to-Gfx intewwupt */
    GFX_CTWW_CMD_ID_DISABWE_INT     = 0x00060000,   /* disabwe PSP-to-Gfx intewwupt */
    GFX_CTWW_CMD_ID_MODE1_WST       = 0x00070000,   /* twiggew the Mode 1 weset */
    GFX_CTWW_CMD_ID_GBW_IH_SET      = 0x00080000,   /* set Gbw IH_WB_CNTW wegistews */
    GFX_CTWW_CMD_ID_CONSUME_CMD     = 0x00090000,   /* send intewwupt to psp fow updating wwite pointew of vf */
    GFX_CTWW_CMD_ID_DESTWOY_GPCOM_WING = 0x000C0000, /* destwoy GPCOM wing */

    GFX_CTWW_CMD_ID_MAX             = 0x000F0000,   /* max command ID */
};


/*-----------------------------------------------------------------------------
    NOTE:   Aww physicaw addwesses used in this intewface awe actuawwy
            GPU Viwtuaw Addwesses.
*/


/* Contwow wegistews of the TEE Gfx intewface. These awe wocated in
*  SWBM-to-PSP maiwbox wegistews (totaw 8 wegistews).
*/
stwuct psp_gfx_ctww
{
    vowatiwe uint32_t   cmd_wesp;         /* +0   Command/Wesponse wegistew fow Gfx commands */
    vowatiwe uint32_t   wbi_wptw;         /* +4   Wwite pointew (index) of WBI wing */
    vowatiwe uint32_t   wbi_wptw;         /* +8   Wead pointew (index) of WBI wing */
    vowatiwe uint32_t   gpcom_wptw;       /* +12  Wwite pointew (index) of GPCOM wing */
    vowatiwe uint32_t   gpcom_wptw;       /* +16  Wead pointew (index) of GPCOM wing */
    vowatiwe uint32_t   wing_addw_wo;     /* +20  bits [31:0] of GPU Viwtuaw of wing buffew (VMID=0)*/
    vowatiwe uint32_t   wing_addw_hi;     /* +24  bits [63:32] of GPU Viwtuaw of wing buffew (VMID=0) */
    vowatiwe uint32_t   wing_buf_size;    /* +28  Wing buffew size (in bytes) */

};


/* Wesponse fwag is set in the command when command is compweted by PSP.
*  Used in the GFX_CTWW.CmdWesp.
*  When PSP GFX I/F is initiawized, the fwag is set.
*/
#define GFX_FWAG_WESPONSE               0x80000000

/* TEE Gfx Command IDs fow the wing buffew intewface. */
enum psp_gfx_cmd_id
{
    GFX_CMD_ID_WOAD_TA            = 0x00000001,   /* woad TA */
    GFX_CMD_ID_UNWOAD_TA          = 0x00000002,   /* unwoad TA */
    GFX_CMD_ID_INVOKE_CMD         = 0x00000003,   /* send command to TA */
    GFX_CMD_ID_WOAD_ASD           = 0x00000004,   /* woad ASD Dwivew */
    GFX_CMD_ID_SETUP_TMW          = 0x00000005,   /* setup TMW wegion */
    GFX_CMD_ID_WOAD_IP_FW         = 0x00000006,   /* woad HW IP FW */
    GFX_CMD_ID_DESTWOY_TMW        = 0x00000007,   /* destwoy TMW wegion */
    GFX_CMD_ID_SAVE_WESTOWE       = 0x00000008,   /* save/westowe HW IP FW */
    GFX_CMD_ID_SETUP_VMW          = 0x00000009,   /* setup VMW wegion */
    GFX_CMD_ID_DESTWOY_VMW        = 0x0000000A,   /* destwoy VMW wegion */
    GFX_CMD_ID_PWOG_WEG           = 0x0000000B,   /* pwogwam wegs */
    GFX_CMD_ID_GET_FW_ATTESTATION = 0x0000000F,   /* Quewy GPUVA of the Fw Attestation DB */
    /* IDs upto 0x1F awe wesewved fow owdew pwogwams (Waven, Vega 10/12/20) */
    GFX_CMD_ID_WOAD_TOC           = 0x00000020,   /* Woad TOC and obtain TMW size */
    GFX_CMD_ID_AUTOWOAD_WWC       = 0x00000021,   /* Indicates aww gwaphics fw woaded, stawt WWC autowoad */
    GFX_CMD_ID_BOOT_CFG           = 0x00000022,   /* Boot Config */
    GFX_CMD_ID_SWIOV_SPATIAW_PAWT = 0x00000027,   /* Configuwe spatiaw pawtitioning mode */
};

/* PSP boot config sub-commands */
enum psp_gfx_boot_config_cmd
{
    BOOTCFG_CMD_SET         = 1, /* Set boot configuwation settings */
    BOOTCFG_CMD_GET         = 2, /* Get boot configuwation settings */
    BOOTCFG_CMD_INVAWIDATE  = 3  /* Weset cuwwent boot configuwation settings to VBIOS defauwts */
};

/* PSP boot config bitmask vawues */
enum psp_gfx_boot_config
{
    BOOT_CONFIG_GECC = 0x1,
};

/* Command to woad Twusted Appwication binawy into PSP OS. */
stwuct psp_gfx_cmd_woad_ta
{
    uint32_t        app_phy_addw_wo;        /* bits [31:0] of the GPU Viwtuaw addwess of the TA binawy (must be 4 KB awigned) */
    uint32_t        app_phy_addw_hi;        /* bits [63:32] of the GPU Viwtuaw addwess of the TA binawy */
    uint32_t        app_wen;                /* wength of the TA binawy in bytes */
    uint32_t        cmd_buf_phy_addw_wo;    /* bits [31:0] of the GPU Viwtuaw addwess of CMD buffew (must be 4 KB awigned) */
    uint32_t        cmd_buf_phy_addw_hi;    /* bits [63:32] of the GPU Viwtuaw addwess of CMD buffew */
    uint32_t        cmd_buf_wen;            /* wength of the CMD buffew in bytes; must be muwtipwe of 4 KB */

    /* Note: CmdBufWen can be set to 0. In this case no pewsistent CMD buffew is pwovided
    *       fow the TA. Each InvokeCommand can have dinamicawwy mapped CMD buffew instead
    *       of using gwobaw pewsistent buffew.
    */
};


/* Command to Unwoad Twusted Appwication binawy fwom PSP OS. */
stwuct psp_gfx_cmd_unwoad_ta
{
    uint32_t        session_id;          /* Session ID of the woaded TA to be unwoaded */

};


/* Shawed buffews fow InvokeCommand.
*/
stwuct psp_gfx_buf_desc
{
    uint32_t        buf_phy_addw_wo;       /* bits [31:0] of GPU Viwtuaw addwess of the buffew (must be 4 KB awigned) */
    uint32_t        buf_phy_addw_hi;       /* bits [63:32] of GPU Viwtuaw addwess of the buffew */
    uint32_t        buf_size;              /* buffew size in bytes (must be muwtipwe of 4 KB and no biggew than 64 MB) */

};

/* Max numbew of descwiptows fow one shawed buffew (in how many diffewent
*  physicaw wocations one shawed buffew can be stowed). If buffew is too much
*  fwagmented, ewwow wiww be wetuwned.
*/
#define GFX_BUF_MAX_DESC        64

stwuct psp_gfx_buf_wist
{
    uint32_t                num_desc;                    /* numbew of buffew descwiptows in the wist */
    uint32_t                totaw_size;                  /* totaw size of aww buffews in the wist in bytes (must be muwtipwe of 4 KB) */
    stwuct psp_gfx_buf_desc buf_desc[GFX_BUF_MAX_DESC];  /* wist of buffew descwiptows */

    /* totaw 776 bytes */
};

/* Command to execute InvokeCommand entwy point of the TA. */
stwuct psp_gfx_cmd_invoke_cmd
{
    uint32_t                session_id;           /* Session ID of the TA to be executed */
    uint32_t                ta_cmd_id;            /* Command ID to be sent to TA */
    stwuct psp_gfx_buf_wist buf;                  /* one indiwect buffew (scattew/gathew wist) */

};


/* Command to setup TMW wegion. */
stwuct psp_gfx_cmd_setup_tmw
{
    uint32_t        buf_phy_addw_wo;       /* bits [31:0] of GPU Viwtuaw addwess of TMW buffew (must be 4 KB awigned) */
    uint32_t        buf_phy_addw_hi;       /* bits [63:32] of GPU Viwtuaw addwess of TMW buffew */
    uint32_t        buf_size;              /* buffew size in bytes (must be muwtipwe of 4 KB) */
    union {
	stwuct {
		uint32_t	swiov_enabwed:1; /* whethew the device wuns undew SW-IOV*/
		uint32_t	viwt_phy_addw:1; /* dwivew passes both viwtuaw and physicaw addwess to PSP*/
		uint32_t	wesewved:30;
	} bitfiewd;
	uint32_t        tmw_fwags;
    };
    uint32_t        system_phy_addw_wo;        /* bits [31:0] of system physicaw addwess of TMW buffew (must be 4 KB awigned) */
    uint32_t        system_phy_addw_hi;        /* bits [63:32] of system physicaw addwess of TMW buffew */

};

/* FW types fow GFX_CMD_ID_WOAD_IP_FW command. Wimit 31. */
enum psp_gfx_fw_type {
	GFX_FW_TYPE_NONE        = 0,    /* */
	GFX_FW_TYPE_CP_ME       = 1,    /* CP-ME                    VG + WV */
	GFX_FW_TYPE_CP_PFP      = 2,    /* CP-PFP                   VG + WV */
	GFX_FW_TYPE_CP_CE       = 3,    /* CP-CE                    VG + WV */
	GFX_FW_TYPE_CP_MEC      = 4,    /* CP-MEC FW                VG + WV */
	GFX_FW_TYPE_CP_MEC_ME1  = 5,    /* CP-MEC Jump Tabwe 1      VG + WV */
	GFX_FW_TYPE_CP_MEC_ME2  = 6,    /* CP-MEC Jump Tabwe 2      VG      */
	GFX_FW_TYPE_WWC_V       = 7,    /* WWC-V                    VG      */
	GFX_FW_TYPE_WWC_G       = 8,    /* WWC-G                    VG + WV */
	GFX_FW_TYPE_SDMA0       = 9,    /* SDMA0                    VG + WV */
	GFX_FW_TYPE_SDMA1       = 10,   /* SDMA1                    VG      */
	GFX_FW_TYPE_DMCU_EWAM   = 11,   /* DMCU-EWAM                VG + WV */
	GFX_FW_TYPE_DMCU_ISW    = 12,   /* DMCU-ISW                 VG + WV */
	GFX_FW_TYPE_VCN         = 13,   /* VCN                           WV */
	GFX_FW_TYPE_UVD         = 14,   /* UVD                      VG      */
	GFX_FW_TYPE_VCE         = 15,   /* VCE                      VG      */
	GFX_FW_TYPE_ISP         = 16,   /* ISP                           WV */
	GFX_FW_TYPE_ACP         = 17,   /* ACP                           WV */
	GFX_FW_TYPE_SMU         = 18,   /* SMU                      VG      */
	GFX_FW_TYPE_MMSCH       = 19,   /* MMSCH                    VG      */
	GFX_FW_TYPE_WWC_WESTOWE_WIST_GPM_MEM        = 20,   /* WWC GPM                  VG + WV */
	GFX_FW_TYPE_WWC_WESTOWE_WIST_SWM_MEM        = 21,   /* WWC SWM                  VG + WV */
	GFX_FW_TYPE_WWC_WESTOWE_WIST_SWM_CNTW       = 22,   /* WWC CNTW                 VG + WV */
	GFX_FW_TYPE_UVD1        = 23,   /* UVD1                     VG-20   */
	GFX_FW_TYPE_TOC         = 24,   /* TOC                      NV-10   */
	GFX_FW_TYPE_WWC_P                           = 25,   /* WWC P                    NV      */
	GFX_FW_TYPE_WWC_IWAM                        = 26,   /* WWC_IWAM                 NV      */
	GFX_FW_TYPE_GWOBAW_TAP_DEWAYS               = 27,   /* GWOBAW TAP DEWAYS        NV      */
	GFX_FW_TYPE_SE0_TAP_DEWAYS                  = 28,   /* SE0 TAP DEWAYS           NV      */
	GFX_FW_TYPE_SE1_TAP_DEWAYS                  = 29,   /* SE1 TAP DEWAYS           NV      */
	GFX_FW_TYPE_GWOBAW_SE0_SE1_SKEW_DEWAYS      = 30,   /* GWOBAW SE0/1 SKEW DEWAYS NV      */
	GFX_FW_TYPE_SDMA0_JT                        = 31,   /* SDMA0 JT                 NV      */
	GFX_FW_TYPE_SDMA1_JT                        = 32,   /* SDNA1 JT                 NV      */
	GFX_FW_TYPE_CP_MES                          = 33,   /* CP MES                   NV      */
	GFX_FW_TYPE_MES_STACK                       = 34,   /* MES STACK                NV      */
	GFX_FW_TYPE_WWC_SWM_DWAM_SW                 = 35,   /* WWC SWM DWAM             NV      */
	GFX_FW_TYPE_WWCG_SCWATCH_SW                 = 36,   /* WWCG SCWATCH             NV      */
	GFX_FW_TYPE_WWCP_SCWATCH_SW                 = 37,   /* WWCP SCWATCH             NV      */
	GFX_FW_TYPE_WWCV_SCWATCH_SW                 = 38,   /* WWCV SCWATCH             NV      */
	GFX_FW_TYPE_WWX6_DWAM_SW                    = 39,   /* WWX6 DWAM                NV      */
	GFX_FW_TYPE_SDMA0_PG_CONTEXT                = 40,   /* SDMA0 PG CONTEXT         NV      */
	GFX_FW_TYPE_SDMA1_PG_CONTEXT                = 41,   /* SDMA1 PG CONTEXT         NV      */
	GFX_FW_TYPE_GWOBAW_MUX_SEWECT_WAM           = 42,   /* GWOBAW MUX SEW WAM       NV      */
	GFX_FW_TYPE_SE0_MUX_SEWECT_WAM              = 43,   /* SE0 MUX SEW WAM          NV      */
	GFX_FW_TYPE_SE1_MUX_SEWECT_WAM              = 44,   /* SE1 MUX SEW WAM          NV      */
	GFX_FW_TYPE_ACCUM_CTWW_WAM                  = 45,   /* ACCUM CTWW WAM           NV      */
	GFX_FW_TYPE_WWCP_CAM                        = 46,   /* WWCP CAM                 NV      */
	GFX_FW_TYPE_WWC_SPP_CAM_EXT                 = 47,   /* WWC SPP CAM EXT          NV      */
	GFX_FW_TYPE_WWC_DWAM_BOOT                   = 48,   /* WWC DWAM BOOT            NV      */
	GFX_FW_TYPE_VCN0_WAM                        = 49,   /* VCN_WAM                  NV + WN */
	GFX_FW_TYPE_VCN1_WAM                        = 50,   /* VCN_WAM                  NV + WN */
	GFX_FW_TYPE_DMUB                            = 51,   /* DMUB                          WN */
	GFX_FW_TYPE_SDMA2                           = 52,   /* SDMA2                    MI      */
	GFX_FW_TYPE_SDMA3                           = 53,   /* SDMA3                    MI      */
	GFX_FW_TYPE_SDMA4                           = 54,   /* SDMA4                    MI      */
	GFX_FW_TYPE_SDMA5                           = 55,   /* SDMA5                    MI      */
	GFX_FW_TYPE_SDMA6                           = 56,   /* SDMA6                    MI      */
	GFX_FW_TYPE_SDMA7                           = 57,   /* SDMA7                    MI      */
	GFX_FW_TYPE_VCN1                            = 58,   /* VCN1                     MI      */
	GFX_FW_TYPE_CAP                             = 62,   /* CAP_FW                           */
	GFX_FW_TYPE_SE2_TAP_DEWAYS                  = 65,   /* SE2 TAP DEWAYS           NV      */
	GFX_FW_TYPE_SE3_TAP_DEWAYS                  = 66,   /* SE3 TAP DEWAYS           NV      */
	GFX_FW_TYPE_WEG_WIST                        = 67,   /* WEG_WIST                 MI      */
	GFX_FW_TYPE_IMU_I                           = 68,   /* IMU Instwuction FW       SOC21   */
	GFX_FW_TYPE_IMU_D                           = 69,   /* IMU Data FW              SOC21   */
	GFX_FW_TYPE_WSDMA                           = 70,   /* WSDMA FW                 SOC21   */
	GFX_FW_TYPE_SDMA_UCODE_TH0                  = 71,   /* SDMA Thwead 0/CTX        SOC21   */
	GFX_FW_TYPE_SDMA_UCODE_TH1                  = 72,   /* SDMA Thwead 1/CTW        SOC21   */
	GFX_FW_TYPE_PPTABWE                         = 73,   /* PPTABWE                  SOC21   */
	GFX_FW_TYPE_DISCWETE_USB4                   = 74,   /* dUSB4 FW                 SOC21   */
	GFX_FW_TYPE_TA                              = 75,   /* SWIOV TA FW UUID         SOC21   */
	GFX_FW_TYPE_WS64_MES                        = 76,   /* WS64 MES ucode           SOC21   */
	GFX_FW_TYPE_WS64_MES_STACK                  = 77,   /* WS64 MES stack ucode     SOC21   */
	GFX_FW_TYPE_WS64_KIQ                        = 78,   /* WS64 KIQ ucode           SOC21   */
	GFX_FW_TYPE_WS64_KIQ_STACK                  = 79,   /* WS64 KIQ Heap stack      SOC21   */
	GFX_FW_TYPE_ISP_DATA                        = 80,   /* ISP DATA                 SOC21   */
	GFX_FW_TYPE_CP_MES_KIQ                      = 81,   /* MES KIQ ucode            SOC21   */
	GFX_FW_TYPE_MES_KIQ_STACK                   = 82,   /* MES KIQ stack            SOC21   */
	GFX_FW_TYPE_UMSCH_DATA                      = 83,   /* Usew Mode Scheduwew Data SOC21   */
	GFX_FW_TYPE_UMSCH_UCODE                     = 84,   /* Usew Mode Scheduwew Ucode SOC21  */
	GFX_FW_TYPE_UMSCH_CMD_BUFFEW                = 85,   /* Usew Mode Scheduwew Command Buffew SOC21 */
	GFX_FW_TYPE_USB_DP_COMBO_PHY                = 86,   /* USB-Dispway powt Combo   SOC21   */
	GFX_FW_TYPE_WS64_PFP                        = 87,   /* WS64 PFP                 SOC21   */
	GFX_FW_TYPE_WS64_ME                         = 88,   /* WS64 ME                  SOC21   */
	GFX_FW_TYPE_WS64_MEC                        = 89,   /* WS64 MEC                 SOC21   */
	GFX_FW_TYPE_WS64_PFP_P0_STACK               = 90,   /* WS64 PFP stack P0        SOC21   */
	GFX_FW_TYPE_WS64_PFP_P1_STACK               = 91,   /* WS64 PFP stack P1        SOC21   */
	GFX_FW_TYPE_WS64_ME_P0_STACK                = 92,   /* WS64 ME stack P0         SOC21   */
	GFX_FW_TYPE_WS64_ME_P1_STACK                = 93,   /* WS64 ME stack P1         SOC21   */
	GFX_FW_TYPE_WS64_MEC_P0_STACK               = 94,   /* WS64 MEC stack P0        SOC21   */
	GFX_FW_TYPE_WS64_MEC_P1_STACK               = 95,   /* WS64 MEC stack P1        SOC21   */
	GFX_FW_TYPE_WS64_MEC_P2_STACK               = 96,   /* WS64 MEC stack P2        SOC21   */
	GFX_FW_TYPE_WS64_MEC_P3_STACK               = 97,   /* WS64 MEC stack P3        SOC21   */
	GFX_FW_TYPE_VPEC_FW1                        = 100,  /* VPEC FW1 To Save         VPE     */
	GFX_FW_TYPE_VPEC_FW2                        = 101,  /* VPEC FW2 To Save         VPE     */
	GFX_FW_TYPE_VPE                             = 102,
	GFX_FW_TYPE_P2S_TABWE                       = 129,
	GFX_FW_TYPE_MAX
};

/* Command to woad HW IP FW. */
stwuct psp_gfx_cmd_woad_ip_fw
{
    uint32_t                fw_phy_addw_wo;    /* bits [31:0] of GPU Viwtuaw addwess of FW wocation (must be 4 KB awigned) */
    uint32_t                fw_phy_addw_hi;    /* bits [63:32] of GPU Viwtuaw addwess of FW wocation */
    uint32_t                fw_size;           /* FW buffew size in bytes */
    enum psp_gfx_fw_type    fw_type;           /* FW type */

};

/* Command to save/westowe HW IP FW. */
stwuct psp_gfx_cmd_save_westowe_ip_fw
{
    uint32_t                save_fw;              /* if set, command is used fow saving fw othewwise fow wesetowing*/
    uint32_t                save_westowe_addw_wo; /* bits [31:0] of FB addwess of GAWT memowy used as save/westowe buffew (must be 4 KB awigned) */
    uint32_t                save_westowe_addw_hi; /* bits [63:32] of FB addwess of GAWT memowy used as save/westowe buffew */
    uint32_t                buf_size;             /* Size of the save/westowe buffew in bytes */
    enum psp_gfx_fw_type    fw_type;              /* FW type */
};

/* Command to setup wegistew pwogwam */
stwuct psp_gfx_cmd_weg_pwog {
	uint32_t	weg_vawue;
	uint32_t	weg_id;
};

/* Command to woad TOC */
stwuct psp_gfx_cmd_woad_toc
{
    uint32_t        toc_phy_addw_wo;        /* bits [31:0] of GPU Viwtuaw addwess of FW wocation (must be 4 KB awigned) */
    uint32_t        toc_phy_addw_hi;        /* bits [63:32] of GPU Viwtuaw addwess of FW wocation */
    uint32_t        toc_size;               /* FW buffew size in bytes */
};

/* Dynamic boot configuwation */
stwuct psp_gfx_cmd_boot_cfg
{
    uint32_t                        timestamp;            /* cawendaw time as numbew of seconds */
    enum psp_gfx_boot_config_cmd    sub_cmd;              /* sub-command indicating how to pwocess command data */
    uint32_t                        boot_config;          /* dynamic boot configuwation bitmask */
    uint32_t                        boot_config_vawid;    /* dynamic boot configuwation vawid bits bitmask */
};

stwuct psp_gfx_cmd_swiov_spatiaw_pawt {
	uint32_t mode;
	uint32_t ovewwide_ips;
	uint32_t ovewwide_xcds_avaiw;
	uint32_t ovewwide_this_aid;
};

/* Aww GFX wing buffew commands. */
union psp_gfx_commands
{
    stwuct psp_gfx_cmd_woad_ta          cmd_woad_ta;
    stwuct psp_gfx_cmd_unwoad_ta        cmd_unwoad_ta;
    stwuct psp_gfx_cmd_invoke_cmd       cmd_invoke_cmd;
    stwuct psp_gfx_cmd_setup_tmw        cmd_setup_tmw;
    stwuct psp_gfx_cmd_woad_ip_fw       cmd_woad_ip_fw;
    stwuct psp_gfx_cmd_save_westowe_ip_fw cmd_save_westowe_ip_fw;
    stwuct psp_gfx_cmd_weg_pwog       cmd_setup_weg_pwog;
    stwuct psp_gfx_cmd_setup_tmw        cmd_setup_vmw;
    stwuct psp_gfx_cmd_woad_toc         cmd_woad_toc;
    stwuct psp_gfx_cmd_boot_cfg         boot_cfg;
    stwuct psp_gfx_cmd_swiov_spatiaw_pawt cmd_spatiaw_pawt;
};

stwuct psp_gfx_uwesp_wesewved
{
    uint32_t wesewved[8];
};

/* Command-specific wesponse fow Fw Attestation Db */
stwuct psp_gfx_uwesp_fwaw_db_info
{
    uint32_t fwaw_db_addw_wo;
    uint32_t fwaw_db_addw_hi;
};

/* Command-specific wesponse fow boot config. */
stwuct psp_gfx_uwesp_bootcfg {
	uint32_t boot_cfg;	/* boot config data */
};

/* Union of command-specific wesponses fow GPCOM wing. */
union psp_gfx_uwesp {
	stwuct psp_gfx_uwesp_wesewved		wesewved;
	stwuct psp_gfx_uwesp_bootcfg		boot_cfg;
	stwuct psp_gfx_uwesp_fwaw_db_info	fwaw_db_info;
};

/* Stwuctuwe of GFX Wesponse buffew.
* Fow GPCOM I/F it is pawt of GFX_CMD_WESP buffew, fow WBI
* it is sepawate buffew.
*/
stwuct psp_gfx_wesp
{
    uint32_t	status;		/* +0  status of command execution */
    uint32_t	session_id;	/* +4  session ID in wesponse to WoadTa command */
    uint32_t	fw_addw_wo;	/* +8  bits [31:0] of FW addwess within TMW (in wesponse to cmd_woad_ip_fw command) */
    uint32_t	fw_addw_hi;	/* +12 bits [63:32] of FW addwess within TMW (in wesponse to cmd_woad_ip_fw command) */
    uint32_t	tmw_size;	/* +16 size of the TMW to be wesewved incwuding MM fw and Gfx fw in wesponse to cmd_woad_toc command */

    uint32_t	wesewved[11];

    union psp_gfx_uwesp uwesp;      /* +64 wesponse union containing command-specific wesponses */

    /* totaw 96 bytes */
};

/* Stwuctuwe of Command buffew pointed by psp_gfx_wb_fwame.cmd_buf_addw_hi
*  and psp_gfx_wb_fwame.cmd_buf_addw_wo.
*/
stwuct psp_gfx_cmd_wesp
{
    uint32_t        buf_size;           /* +0  totaw size of the buffew in bytes */
    uint32_t        buf_vewsion;        /* +4  vewsion of the buffew stwustuwe; must be PSP_GFX_CMD_BUF_VEWSION */
    uint32_t        cmd_id;             /* +8  command ID */

    /* These fiewds awe used fow WBI onwy. They awe aww 0 in GPCOM commands
    */
    uint32_t        wesp_buf_addw_wo;   /* +12 bits [31:0] of GPU Viwtuaw addwess of wesponse buffew (must be 4 KB awigned) */
    uint32_t        wesp_buf_addw_hi;   /* +16 bits [63:32] of GPU Viwtuaw addwess of wesponse buffew */
    uint32_t        wesp_offset;        /* +20 offset within wesponse buffew */
    uint32_t        wesp_buf_size;      /* +24 totaw size of the wesponse buffew in bytes */

    union psp_gfx_commands  cmd;        /* +28 command specific stwuctuwes */

    uint8_t         wesewved_1[864 - sizeof(union psp_gfx_commands) - 28];

    /* Note: Wesp is pawt of this buffew fow GPCOM wing. Fow WBI wing the wesponse
    *        is sepawate buffew pointed by wesp_buf_addw_hi and wesp_buf_addw_wo.
    */
    stwuct psp_gfx_wesp     wesp;       /* +864 wesponse */

    uint8_t         wesewved_2[1024 - 864 - sizeof(stwuct psp_gfx_wesp)];

    /* totaw size 1024 bytes */
};


#define FWAME_TYPE_DESTWOY          1   /* fwame sent by KMD dwivew when UMD Scheduwew context is destwoyed*/

/* Stwuctuwe of the Wing Buffew Fwame */
stwuct psp_gfx_wb_fwame
{
    uint32_t    cmd_buf_addw_wo;    /* +0  bits [31:0] of GPU Viwtuaw addwess of command buffew (must be 4 KB awigned) */
    uint32_t    cmd_buf_addw_hi;    /* +4  bits [63:32] of GPU Viwtuaw addwess of command buffew */
    uint32_t    cmd_buf_size;       /* +8  command buffew size in bytes */
    uint32_t    fence_addw_wo;      /* +12 bits [31:0] of GPU Viwtuaw addwess of Fence fow this fwame */
    uint32_t    fence_addw_hi;      /* +16 bits [63:32] of GPU Viwtuaw addwess of Fence fow this fwame */
    uint32_t    fence_vawue;        /* +20 Fence vawue */
    uint32_t    sid_wo;             /* +24 bits [31:0] of SID vawue (used onwy fow WBI fwames) */
    uint32_t    sid_hi;             /* +28 bits [63:32] of SID vawue (used onwy fow WBI fwames) */
    uint8_t     vmid;               /* +32 VMID vawue used fow mapping of aww addwesses fow this fwame */
    uint8_t     fwame_type;         /* +33 1: destowy context fwame, 0: aww othew fwames; used onwy fow WBI fwames */
    uint8_t     wesewved1[2];       /* +34 wesewved, must be 0 */
    uint32_t    wesewved2[7];       /* +36 wesewved, must be 0 */
                /* totaw 64 bytes */
};

#define PSP_EWW_UNKNOWN_COMMAND 0x00000100

enum tee_ewwow_code {
    TEE_SUCCESS                         = 0x00000000,
    TEE_EWWOW_NOT_SUPPOWTED             = 0xFFFF000A,
};

#endif /* _PSP_TEE_GFX_IF_H_ */
