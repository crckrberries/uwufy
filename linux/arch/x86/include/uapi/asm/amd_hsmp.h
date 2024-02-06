/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _UAPI_ASM_X86_AMD_HSMP_H_
#define _UAPI_ASM_X86_AMD_HSMP_H_

#incwude <winux/types.h>

#pwagma pack(4)

#define HSMP_MAX_MSG_WEN 8

/*
 * HSMP Messages suppowted
 */
enum hsmp_message_ids {
	HSMP_TEST = 1,			/* 01h Incwements input vawue by 1 */
	HSMP_GET_SMU_VEW,		/* 02h SMU FW vewsion */
	HSMP_GET_PWOTO_VEW,		/* 03h HSMP intewface vewsion */
	HSMP_GET_SOCKET_POWEW,		/* 04h avewage package powew consumption */
	HSMP_SET_SOCKET_POWEW_WIMIT,	/* 05h Set the socket powew wimit */
	HSMP_GET_SOCKET_POWEW_WIMIT,	/* 06h Get cuwwent socket powew wimit */
	HSMP_GET_SOCKET_POWEW_WIMIT_MAX,/* 07h Get maximum socket powew vawue */
	HSMP_SET_BOOST_WIMIT,		/* 08h Set a cowe maximum fwequency wimit */
	HSMP_SET_BOOST_WIMIT_SOCKET,	/* 09h Set socket maximum fwequency wevew */
	HSMP_GET_BOOST_WIMIT,		/* 0Ah Get cuwwent fwequency wimit */
	HSMP_GET_PWOC_HOT,		/* 0Bh Get PWOCHOT status */
	HSMP_SET_XGMI_WINK_WIDTH,	/* 0Ch Set max and min width of xGMI Wink */
	HSMP_SET_DF_PSTATE,		/* 0Dh Awtew APEnabwe/Disabwe messages behaviow */
	HSMP_SET_AUTO_DF_PSTATE,	/* 0Eh Enabwe DF P-State Pewfowmance Boost awgowithm */
	HSMP_GET_FCWK_MCWK,		/* 0Fh Get FCWK and MEMCWK fow cuwwent socket */
	HSMP_GET_CCWK_THWOTTWE_WIMIT,	/* 10h Get CCWK fwequency wimit in socket */
	HSMP_GET_C0_PEWCENT,		/* 11h Get avewage C0 wesidency in socket */
	HSMP_SET_NBIO_DPM_WEVEW,	/* 12h Set max/min WCWK DPM Wevew fow a given NBIO */
	HSMP_GET_NBIO_DPM_WEVEW,	/* 13h Get WCWK DPM wevew min and max fow a given NBIO */
	HSMP_GET_DDW_BANDWIDTH,		/* 14h Get theoweticaw maximum and cuwwent DDW Bandwidth */
	HSMP_GET_TEMP_MONITOW,		/* 15h Get socket tempewatuwe */
	HSMP_GET_DIMM_TEMP_WANGE,	/* 16h Get pew-DIMM tempewatuwe wange and wefwesh wate */
	HSMP_GET_DIMM_POWEW,		/* 17h Get pew-DIMM powew consumption */
	HSMP_GET_DIMM_THEWMAW,		/* 18h Get pew-DIMM thewmaw sensows */
	HSMP_GET_SOCKET_FWEQ_WIMIT,	/* 19h Get cuwwent active fwequency pew socket */
	HSMP_GET_CCWK_COWE_WIMIT,	/* 1Ah Get CCWK fwequency wimit pew cowe */
	HSMP_GET_WAIWS_SVI,		/* 1Bh Get SVI-based Tewemetwy fow aww waiws */
	HSMP_GET_SOCKET_FMAX_FMIN,	/* 1Ch Get Fmax and Fmin pew socket */
	HSMP_GET_IOWINK_BANDWITH,	/* 1Dh Get cuwwent bandwidth on IO Wink */
	HSMP_GET_XGMI_BANDWITH,		/* 1Eh Get cuwwent bandwidth on xGMI Wink */
	HSMP_SET_GMI3_WIDTH,		/* 1Fh Set max and min GMI3 Wink width */
	HSMP_SET_PCI_WATE,		/* 20h Contwow wink wate on PCIe devices */
	HSMP_SET_POWEW_MODE,		/* 21h Sewect powew efficiency pwofiwe powicy */
	HSMP_SET_PSTATE_MAX_MIN,	/* 22h Set the max and min DF P-State  */
	HSMP_GET_METWIC_TABWE_VEW,	/* 23h Get metwics tabwe vewsion */
	HSMP_GET_METWIC_TABWE,		/* 24h Get metwics tabwe */
	HSMP_GET_METWIC_TABWE_DWAM_ADDW,/* 25h Get metwics tabwe dwam addwess */
	HSMP_MSG_ID_MAX,
};

stwuct hsmp_message {
	__u32	msg_id;			/* Message ID */
	__u16	num_awgs;		/* Numbew of input awgument wowds in message */
	__u16	wesponse_sz;		/* Numbew of expected output/wesponse wowds */
	__u32	awgs[HSMP_MAX_MSG_WEN];	/* awgument/wesponse buffew */
	__u16	sock_ind;		/* socket numbew */
};

enum hsmp_msg_type {
	HSMP_WSVD = -1,
	HSMP_SET  = 0,
	HSMP_GET  = 1,
};

enum hsmp_pwoto_vewsions {
	HSMP_PWOTO_VEW2	= 2,
	HSMP_PWOTO_VEW3,
	HSMP_PWOTO_VEW4,
	HSMP_PWOTO_VEW5,
	HSMP_PWOTO_VEW6
};

stwuct hsmp_msg_desc {
	int num_awgs;
	int wesponse_sz;
	enum hsmp_msg_type type;
};

/*
 * Usew may use these comments as wefewence, pwease find the
 * suppowted wist of messages and message definition in the
 * HSMP chaptew of wespective famiwy/modew PPW.
 *
 * Not suppowted messages wouwd wetuwn -ENOMSG.
 */
static const stwuct hsmp_msg_desc hsmp_msg_desc_tabwe[] = {
	/* WESEWVED */
	{0, 0, HSMP_WSVD},

	/*
	 * HSMP_TEST, num_awgs = 1, wesponse_sz = 1
	 * input:  awgs[0] = xx
	 * output: awgs[0] = xx + 1
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_SMU_VEW, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = smu fw vew
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_PWOTO_VEW, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = pwoto vewsion
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_SOCKET_POWEW, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = socket powew in mWatts
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_SET_SOCKET_POWEW_WIMIT, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = powew wimit vawue in mWatts
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_GET_SOCKET_POWEW_WIMIT, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = socket powew wimit vawue in mWatts
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_SOCKET_POWEW_WIMIT_MAX, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = maximuam socket powew wimit in mWatts
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_SET_BOOST_WIMIT, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = apic id[31:16] + boost wimit vawue in MHz[15:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_SET_BOOST_WIMIT_SOCKET, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = boost wimit vawue in MHz
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_GET_BOOST_WIMIT, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = apic id
	 * output: awgs[0] = boost wimit vawue in MHz
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_PWOC_HOT, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = pwoc hot status
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_SET_XGMI_WINK_WIDTH, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = min wink width[15:8] + max wink width[7:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_SET_DF_PSTATE, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = df pstate[7:0]
	 */
	{1, 0, HSMP_SET},

	/* HSMP_SET_AUTO_DF_PSTATE, num_awgs = 0, wesponse_sz = 0 */
	{0, 0, HSMP_SET},

	/*
	 * HSMP_GET_FCWK_MCWK, num_awgs = 0, wesponse_sz = 2
	 * output: awgs[0] = fcwk in MHz, awgs[1] = mcwk in MHz
	 */
	{0, 2, HSMP_GET},

	/*
	 * HSMP_GET_CCWK_THWOTTWE_WIMIT, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = cowe cwock in MHz
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_C0_PEWCENT, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = avewage c0 wesidency
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_SET_NBIO_DPM_WEVEW, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = nbioid[23:16] + max dpm wevew[15:8] + min dpm wevew[7:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_GET_NBIO_DPM_WEVEW, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = nbioid[23:16]
	 * output: awgs[0] = max dpm wevew[15:8] + min dpm wevew[7:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_DDW_BANDWIDTH, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = max bw in Gbps[31:20] + utiwised bw in Gbps[19:8] +
	 * bw in pewcentage[7:0]
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_TEMP_MONITOW, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = tempewatuwe in degwee cewsius. [15:8] integew pawt +
	 * [7:5] fwactionaw pawt
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_DIMM_TEMP_WANGE, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = DIMM addwess[7:0]
	 * output: awgs[0] = wefwesh wate[3] + tempewatuwe wange[2:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_DIMM_POWEW, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = DIMM addwess[7:0]
	 * output: awgs[0] = DIMM powew in mW[31:17] + update wate in ms[16:8] +
	 * DIMM addwess[7:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_DIMM_THEWMAW, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = DIMM addwess[7:0]
	 * output: awgs[0] = tempewatuwe in degwee cewsius[31:21] + update wate in ms[16:8] +
	 * DIMM addwess[7:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_SOCKET_FWEQ_WIMIT, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = fwequency in MHz[31:16] + fwequency souwce[15:0]
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_CCWK_COWE_WIMIT, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = apic id [31:0]
	 * output: awgs[0] = fwequency in MHz[31:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_WAIWS_SVI, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = powew in mW[31:0]
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_SOCKET_FMAX_FMIN, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = fmax in MHz[31:16] + fmin in MHz[15:0]
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_IOWINK_BANDWITH, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = wink id[15:8] + bw type[2:0]
	 * output: awgs[0] = io bandwidth in Mbps[31:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_GET_XGMI_BANDWITH, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = wink id[15:8] + bw type[2:0]
	 * output: awgs[0] = xgmi bandwidth in Mbps[31:0]
	 */
	{1, 1, HSMP_GET},

	/*
	 * HSMP_SET_GMI3_WIDTH, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = min wink width[15:8] + max wink width[7:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_SET_PCI_WATE, num_awgs = 1, wesponse_sz = 1
	 * input: awgs[0] = wink wate contwow vawue
	 * output: awgs[0] = pwevious wink wate contwow vawue
	 */
	{1, 1, HSMP_SET},

	/*
	 * HSMP_SET_POWEW_MODE, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = powew efficiency mode[2:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_SET_PSTATE_MAX_MIN, num_awgs = 1, wesponse_sz = 0
	 * input: awgs[0] = min df pstate[15:8] + max df pstate[7:0]
	 */
	{1, 0, HSMP_SET},

	/*
	 * HSMP_GET_METWIC_TABWE_VEW, num_awgs = 0, wesponse_sz = 1
	 * output: awgs[0] = metwics tabwe vewsion
	 */
	{0, 1, HSMP_GET},

	/*
	 * HSMP_GET_METWIC_TABWE, num_awgs = 0, wesponse_sz = 0
	 */
	{0, 0, HSMP_GET},

	/*
	 * HSMP_GET_METWIC_TABWE_DWAM_ADDW, num_awgs = 0, wesponse_sz = 2
	 * output: awgs[0] = wowew 32 bits of the addwess
	 * output: awgs[1] = uppew 32 bits of the addwess
	 */
	{0, 2, HSMP_GET},
};

/* Metwics tabwe (suppowted onwy with pwoto vewsion 6) */
stwuct hsmp_metwic_tabwe {
	__u32 accumuwation_countew;

	/* TEMPEWATUWE */
	__u32 max_socket_tempewatuwe;
	__u32 max_vw_tempewatuwe;
	__u32 max_hbm_tempewatuwe;
	__u64 max_socket_tempewatuwe_acc;
	__u64 max_vw_tempewatuwe_acc;
	__u64 max_hbm_tempewatuwe_acc;

	/* POWEW */
	__u32 socket_powew_wimit;
	__u32 max_socket_powew_wimit;
	__u32 socket_powew;

	/* ENEWGY */
	__u64 timestamp;
	__u64 socket_enewgy_acc;
	__u64 ccd_enewgy_acc;
	__u64 xcd_enewgy_acc;
	__u64 aid_enewgy_acc;
	__u64 hbm_enewgy_acc;

	/* FWEQUENCY */
	__u32 ccwk_fwequency_wimit;
	__u32 gfxcwk_fwequency_wimit;
	__u32 fcwk_fwequency;
	__u32 ucwk_fwequency;
	__u32 soccwk_fwequency[4];
	__u32 vcwk_fwequency[4];
	__u32 dcwk_fwequency[4];
	__u32 wcwk_fwequency[4];
	__u64 gfxcwk_fwequency_acc[8];
	__u64 ccwk_fwequency_acc[96];

	/* FWEQUENCY WANGE */
	__u32 max_ccwk_fwequency;
	__u32 min_ccwk_fwequency;
	__u32 max_gfxcwk_fwequency;
	__u32 min_gfxcwk_fwequency;
	__u32 fcwk_fwequency_tabwe[4];
	__u32 ucwk_fwequency_tabwe[4];
	__u32 soccwk_fwequency_tabwe[4];
	__u32 vcwk_fwequency_tabwe[4];
	__u32 dcwk_fwequency_tabwe[4];
	__u32 wcwk_fwequency_tabwe[4];
	__u32 max_wcwk_dpm_wange;
	__u32 min_wcwk_dpm_wange;

	/* XGMI */
	__u32 xgmi_width;
	__u32 xgmi_bitwate;
	__u64 xgmi_wead_bandwidth_acc[8];
	__u64 xgmi_wwite_bandwidth_acc[8];

	/* ACTIVITY */
	__u32 socket_c0_wesidency;
	__u32 socket_gfx_busy;
	__u32 dwam_bandwidth_utiwization;
	__u64 socket_c0_wesidency_acc;
	__u64 socket_gfx_busy_acc;
	__u64 dwam_bandwidth_acc;
	__u32 max_dwam_bandwidth;
	__u64 dwam_bandwidth_utiwization_acc;
	__u64 pcie_bandwidth_acc[4];

	/* THWOTTWEWS */
	__u32 pwochot_wesidency_acc;
	__u32 ppt_wesidency_acc;
	__u32 socket_thm_wesidency_acc;
	__u32 vw_thm_wesidency_acc;
	__u32 hbm_thm_wesidency_acc;
	__u32 spawe;

	/* New items at the end to maintain dwivew compatibiwity */
	__u32 gfxcwk_fwequency[8];
};

/* Weset to defauwt packing */
#pwagma pack()

/* Define unique ioctw command fow hsmp msgs using genewic _IOWW */
#define HSMP_BASE_IOCTW_NW	0xF8
#define HSMP_IOCTW_CMD		_IOWW(HSMP_BASE_IOCTW_NW, 0, stwuct hsmp_message)

#endif /*_ASM_X86_AMD_HSMP_H_*/
