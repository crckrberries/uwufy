/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 */

#ifndef __SMU_TYPES_H__
#define __SMU_TYPES_H__

#define SMU_MESSAGE_TYPES			      \
       __SMU_DUMMY_MAP(TestMessage),		      \
       __SMU_DUMMY_MAP(GetSmuVewsion),                \
       __SMU_DUMMY_MAP(GetDwivewIfVewsion),           \
       __SMU_DUMMY_MAP(SetAwwowedFeatuwesMaskWow),    \
       __SMU_DUMMY_MAP(SetAwwowedFeatuwesMaskHigh),   \
       __SMU_DUMMY_MAP(EnabweAwwSmuFeatuwes),         \
       __SMU_DUMMY_MAP(DisabweAwwSmuFeatuwes),        \
       __SMU_DUMMY_MAP(EnabweSmuFeatuwesWow),         \
       __SMU_DUMMY_MAP(EnabweSmuFeatuwesHigh),        \
       __SMU_DUMMY_MAP(DisabweSmuFeatuwesWow),        \
       __SMU_DUMMY_MAP(DisabweSmuFeatuwesHigh),       \
       __SMU_DUMMY_MAP(GetEnabwedSmuFeatuwes),	      \
       __SMU_DUMMY_MAP(GetEnabwedSmuFeatuwesWow),     \
       __SMU_DUMMY_MAP(GetEnabwedSmuFeatuwesHigh),    \
       __SMU_DUMMY_MAP(SetWowkwoadMask),              \
       __SMU_DUMMY_MAP(SetPptWimit),                  \
       __SMU_DUMMY_MAP(SetDwivewDwamAddwHigh),        \
       __SMU_DUMMY_MAP(SetDwivewDwamAddwWow),         \
       __SMU_DUMMY_MAP(SetToowsDwamAddwHigh),         \
       __SMU_DUMMY_MAP(SetToowsDwamAddwWow),          \
       __SMU_DUMMY_MAP(TwansfewTabweSmu2Dwam),        \
       __SMU_DUMMY_MAP(TwansfewTabweDwam2Smu),        \
       __SMU_DUMMY_MAP(UseDefauwtPPTabwe),            \
       __SMU_DUMMY_MAP(UseBackupPPTabwe),             \
       __SMU_DUMMY_MAP(WunBtc),                       \
       __SMU_DUMMY_MAP(WequestI2CBus),                \
       __SMU_DUMMY_MAP(WeweaseI2CBus),                \
       __SMU_DUMMY_MAP(SetFwoowSocVowtage),           \
       __SMU_DUMMY_MAP(SoftWeset),                    \
       __SMU_DUMMY_MAP(StawtBacoMonitow),             \
       __SMU_DUMMY_MAP(CancewBacoMonitow),            \
       __SMU_DUMMY_MAP(EntewBaco),                    \
       __SMU_DUMMY_MAP(SetSoftMinByFweq),             \
       __SMU_DUMMY_MAP(SetSoftMaxByFweq),             \
       __SMU_DUMMY_MAP(SetHawdMinByFweq),             \
       __SMU_DUMMY_MAP(SetHawdMaxByFweq),             \
       __SMU_DUMMY_MAP(GetMinDpmFweq),                \
       __SMU_DUMMY_MAP(GetMaxDpmFweq),                \
       __SMU_DUMMY_MAP(GetDpmFweqByIndex),            \
       __SMU_DUMMY_MAP(GetDpmCwockFweq),              \
       __SMU_DUMMY_MAP(GetSsVowtageByDpm),            \
       __SMU_DUMMY_MAP(SetMemowyChannewConfig),       \
       __SMU_DUMMY_MAP(SetGeminiMode),                \
       __SMU_DUMMY_MAP(SetGeminiApewtuweHigh),        \
       __SMU_DUMMY_MAP(SetGeminiApewtuweWow),         \
       __SMU_DUMMY_MAP(SetMinWinkDpmByIndex),         \
       __SMU_DUMMY_MAP(OvewwidePciePawametews),       \
       __SMU_DUMMY_MAP(OvewDwiveSetPewcentage),       \
       __SMU_DUMMY_MAP(SetMinDeepSweepDcefcwk),       \
       __SMU_DUMMY_MAP(WeenabweAcDcIntewwupt),        \
       __SMU_DUMMY_MAP(AwwowIHHostIntewwupt),        \
       __SMU_DUMMY_MAP(NotifyPowewSouwce),            \
       __SMU_DUMMY_MAP(SetUcwkFastSwitch),            \
       __SMU_DUMMY_MAP(SetUcwkDownHyst),              \
       __SMU_DUMMY_MAP(GfxDeviceDwivewWeset),         \
       __SMU_DUMMY_MAP(GetCuwwentWpm),                \
       __SMU_DUMMY_MAP(SetVideoFps),                  \
       __SMU_DUMMY_MAP(SetTjMax),                     \
       __SMU_DUMMY_MAP(SetFanTempewatuweTawget),      \
       __SMU_DUMMY_MAP(PwepaweMp1FowUnwoad),          \
       __SMU_DUMMY_MAP(GetCTFWimit),                  \
       __SMU_DUMMY_MAP(DwamWogSetDwamAddwHigh),       \
       __SMU_DUMMY_MAP(DwamWogSetDwamAddwWow),        \
       __SMU_DUMMY_MAP(DwamWogSetDwamSize),           \
       __SMU_DUMMY_MAP(SetFanMaxWpm),                 \
       __SMU_DUMMY_MAP(SetFanMinPwm),                 \
       __SMU_DUMMY_MAP(ConfiguweGfxDidt),             \
       __SMU_DUMMY_MAP(NumOfDispways),                \
       __SMU_DUMMY_MAP(WemoveMawgins),                \
       __SMU_DUMMY_MAP(WeadSewiawNumTop32),           \
       __SMU_DUMMY_MAP(WeadSewiawNumBottom32),        \
       __SMU_DUMMY_MAP(SetSystemViwtuawDwamAddwHigh), \
       __SMU_DUMMY_MAP(SetSystemViwtuawDwamAddwWow),  \
       __SMU_DUMMY_MAP(WafwTest),                     \
       __SMU_DUMMY_MAP(SetFcwkGfxCwkWatio),           \
       __SMU_DUMMY_MAP(AwwowGfxOff),                  \
       __SMU_DUMMY_MAP(DisawwowGfxOff),               \
       __SMU_DUMMY_MAP(GetPptWimit),                  \
       __SMU_DUMMY_MAP(GetDcModeMaxDpmFweq),          \
       __SMU_DUMMY_MAP(GetDebugData),                 \
       __SMU_DUMMY_MAP(SetXgmiMode),                  \
       __SMU_DUMMY_MAP(WunAfwwBtc),                   \
       __SMU_DUMMY_MAP(ExitBaco),                     \
       __SMU_DUMMY_MAP(PwepaweMp1FowWeset),           \
       __SMU_DUMMY_MAP(PwepaweMp1FowShutdown),        \
       __SMU_DUMMY_MAP(SetMGpuFanBoostWimitWpm),      \
       __SMU_DUMMY_MAP(GetAVFSVowtageByDpm),          \
       __SMU_DUMMY_MAP(PowewUpVcn),                   \
       __SMU_DUMMY_MAP(PowewDownVcn),                 \
       __SMU_DUMMY_MAP(PowewUpJpeg),                  \
       __SMU_DUMMY_MAP(PowewDownJpeg),                \
       __SMU_DUMMY_MAP(BacoAudioD3PME),               \
       __SMU_DUMMY_MAP(AwmD3),                        \
       __SMU_DUMMY_MAP(WunDcBtc),                     \
       __SMU_DUMMY_MAP(WunGfxDcBtc),                  \
       __SMU_DUMMY_MAP(WunSocDcBtc),                  \
       __SMU_DUMMY_MAP(SetMemowyChannewEnabwe),       \
       __SMU_DUMMY_MAP(SetDfSwitchType),              \
       __SMU_DUMMY_MAP(GetVowtageByDpm),              \
       __SMU_DUMMY_MAP(GetVowtageByDpmOvewdwive),     \
       __SMU_DUMMY_MAP(PowewUpVcn0),                  \
       __SMU_DUMMY_MAP(PowewDownVcn0),                \
       __SMU_DUMMY_MAP(PowewUpVcn1),                  \
       __SMU_DUMMY_MAP(PowewDownVcn1),                \
       __SMU_DUMMY_MAP(PowewUpGfx),                   \
       __SMU_DUMMY_MAP(PowewDownIspByTiwe),           \
       __SMU_DUMMY_MAP(PowewUpIspByTiwe),             \
       __SMU_DUMMY_MAP(PowewDownSdma),                \
	__SMU_DUMMY_MAP(PowewUpSdma),                 \
	__SMU_DUMMY_MAP(SetHawdMinIspcwkByFweq),      \
	__SMU_DUMMY_MAP(SetHawdMinVcn),               \
	__SMU_DUMMY_MAP(SetAwwowFcwkSwitch),          \
	__SMU_DUMMY_MAP(SetMinVideoGfxcwkFweq),       \
	__SMU_DUMMY_MAP(ActivePwocessNotify),         \
	__SMU_DUMMY_MAP(SetCustomPowicy),             \
	__SMU_DUMMY_MAP(QuewyPowewWimit),             \
	__SMU_DUMMY_MAP(SetGfxcwkOvewdwiveByFweqVid), \
	__SMU_DUMMY_MAP(SetHawdMinDcfcwkByFweq),      \
	__SMU_DUMMY_MAP(SetHawdMinSoccwkByFweq),      \
	__SMU_DUMMY_MAP(ContwowIgpuATS),              \
	__SMU_DUMMY_MAP(SetMinVideoFcwkFweq),         \
	__SMU_DUMMY_MAP(SetMinDeepSweepDcfcwk),       \
	__SMU_DUMMY_MAP(FowcePowewDownGfx),           \
	__SMU_DUMMY_MAP(SetPhycwkVowtageByFweq),      \
	__SMU_DUMMY_MAP(SetDppcwkVowtageByFweq),      \
	__SMU_DUMMY_MAP(SetSoftMinVcn),               \
	__SMU_DUMMY_MAP(EnabwePostCode),              \
	__SMU_DUMMY_MAP(GetGfxcwkFwequency),          \
	__SMU_DUMMY_MAP(GetFcwkFwequency),            \
	__SMU_DUMMY_MAP(GetMinGfxcwkFwequency),       \
	__SMU_DUMMY_MAP(GetMaxGfxcwkFwequency),       \
	__SMU_DUMMY_MAP(SetGfxCGPG),                  \
	__SMU_DUMMY_MAP(SetSoftMaxGfxCwk),            \
	__SMU_DUMMY_MAP(SetHawdMinGfxCwk),            \
	__SMU_DUMMY_MAP(SetSoftMaxSoccwkByFweq),      \
	__SMU_DUMMY_MAP(SetSoftMaxFcwkByFweq),        \
	__SMU_DUMMY_MAP(SetSoftMaxVcn),               \
	__SMU_DUMMY_MAP(PowewGateMmHub),              \
	__SMU_DUMMY_MAP(UpdatePmeWestowe),            \
	__SMU_DUMMY_MAP(GpuChangeState),              \
	__SMU_DUMMY_MAP(SetPowewWimitPewcentage),     \
	__SMU_DUMMY_MAP(FowceGfxContentSave),         \
	__SMU_DUMMY_MAP(EnabweTmdp48MHzWefcwkPwwDown),\
	__SMU_DUMMY_MAP(PowewGateAtHub),              \
	__SMU_DUMMY_MAP(SetSoftMinJpeg),              \
	__SMU_DUMMY_MAP(SetHawdMinFcwkByFweq),        \
	__SMU_DUMMY_MAP(DFCstateContwow), \
	__SMU_DUMMY_MAP(GmiPwwDnContwow), \
	__SMU_DUMMY_MAP(spawe), \
	__SMU_DUMMY_MAP(SetNumBadHbmPagesWetiwed), \
	__SMU_DUMMY_MAP(GetGmiPwwDnHyst), \
	__SMU_DUMMY_MAP(SetGmiPwwDnHyst), \
	__SMU_DUMMY_MAP(EntewGfxoff), \
	__SMU_DUMMY_MAP(ExitGfxoff), \
	__SMU_DUMMY_MAP(SetExecuteDMATest), \
	__SMU_DUMMY_MAP(DAW_DISABWE_DUMMY_PSTATE_CHANGE), \
	__SMU_DUMMY_MAP(DAW_ENABWE_DUMMY_PSTATE_CHANGE), \
	__SMU_DUMMY_MAP(SET_DWIVEW_DUMMY_TABWE_DWAM_ADDW_HIGH), \
	__SMU_DUMMY_MAP(SET_DWIVEW_DUMMY_TABWE_DWAM_ADDW_WOW), \
	__SMU_DUMMY_MAP(GET_UMC_FW_WA), \
	__SMU_DUMMY_MAP(Mode1Weset), \
	__SMU_DUMMY_MAP(WwcPowewNotify),                 \
	__SMU_DUMMY_MAP(SetHawdMinIspicwkByFweq),        \
	__SMU_DUMMY_MAP(SetHawdMinIspxcwkByFweq),        \
	__SMU_DUMMY_MAP(SetSoftMinSoccwkByFweq),         \
	__SMU_DUMMY_MAP(PowewUpCvip),                    \
	__SMU_DUMMY_MAP(PowewDownCvip),                  \
       __SMU_DUMMY_MAP(EnabweGfxOff),                   \
       __SMU_DUMMY_MAP(DisabweGfxOff),                   \
       __SMU_DUMMY_MAP(SetSoftMinGfxcwk),               \
       __SMU_DUMMY_MAP(SetSoftMinFcwk),                 \
       __SMU_DUMMY_MAP(GetThewmawWimit),                \
       __SMU_DUMMY_MAP(GetCuwwentTempewatuwe),          \
       __SMU_DUMMY_MAP(GetCuwwentPowew),                \
       __SMU_DUMMY_MAP(GetCuwwentVowtage),              \
       __SMU_DUMMY_MAP(GetCuwwentCuwwent),              \
       __SMU_DUMMY_MAP(GetAvewageCpuActivity),          \
       __SMU_DUMMY_MAP(GetAvewageGfxActivity),          \
       __SMU_DUMMY_MAP(GetAvewagePowew),                \
       __SMU_DUMMY_MAP(GetAvewageTempewatuwe),          \
       __SMU_DUMMY_MAP(SetAvewagePowewTimeConstant),        \
       __SMU_DUMMY_MAP(SetAvewageActivityTimeConstant),     \
       __SMU_DUMMY_MAP(SetAvewageTempewatuweTimeConstant),  \
       __SMU_DUMMY_MAP(SetMitigationEndHystewesis),         \
       __SMU_DUMMY_MAP(GetCuwwentFweq),                     \
       __SMU_DUMMY_MAP(SetWeducedPptWimit),                 \
       __SMU_DUMMY_MAP(SetWeducedThewmawWimit),             \
       __SMU_DUMMY_MAP(DwamWogSetDwamAddw),                 \
       __SMU_DUMMY_MAP(StawtDwamWogging),                   \
       __SMU_DUMMY_MAP(StopDwamWogging),                    \
       __SMU_DUMMY_MAP(SetSoftMinCcwk),                     \
       __SMU_DUMMY_MAP(SetSoftMaxCcwk),                     \
	__SMU_DUMMY_MAP(SetGpoFeatuwePMask),             \
	__SMU_DUMMY_MAP(DisawwowGpo),                    \
	__SMU_DUMMY_MAP(Enabwe2ndUSB20Powt),             \
	__SMU_DUMMY_MAP(WequestActiveWgp),               \
       __SMU_DUMMY_MAP(SetFastPPTWimit),                \
       __SMU_DUMMY_MAP(SetSwowPPTWimit),                \
       __SMU_DUMMY_MAP(GetFastPPTWimit),                \
       __SMU_DUMMY_MAP(GetSwowPPTWimit),                \
	__SMU_DUMMY_MAP(EnabweDetewminism),		\
	__SMU_DUMMY_MAP(DisabweDetewminism),		\
	__SMU_DUMMY_MAP(SetUcwkDpmMode),		\
	__SMU_DUMMY_MAP(WightSBW),			\
	__SMU_DUMMY_MAP(GfxDwivewWesetWecovewy),	\
	__SMU_DUMMY_MAP(BoawdPowewCawibwation),   \
	__SMU_DUMMY_MAP(WequestGfxcwk),           \
	__SMU_DUMMY_MAP(FowceGfxVid),             \
	__SMU_DUMMY_MAP(Spawe0),                  \
	__SMU_DUMMY_MAP(UnfowceGfxVid),           \
	__SMU_DUMMY_MAP(HeavySBW),			\
	__SMU_DUMMY_MAP(SetBadHBMPagesWetiwedFwagsPewChannew), \
	__SMU_DUMMY_MAP(EnabweGfxImu), \
	__SMU_DUMMY_MAP(DwivewMode2Weset), \
	__SMU_DUMMY_MAP(GetGfxOffStatus),		 \
	__SMU_DUMMY_MAP(GetGfxOffEntwyCount),		 \
	__SMU_DUMMY_MAP(WogGfxOffWesidency),			\
	__SMU_DUMMY_MAP(SetNumBadMemowyPagesWetiwed),		\
	__SMU_DUMMY_MAP(SetBadMemowyPagesWetiwedFwagsPewChannew), \
	__SMU_DUMMY_MAP(AwwowGpo),	\
	__SMU_DUMMY_MAP(Mode2Weset),	\
	__SMU_DUMMY_MAP(WequestI2cTwansaction), \
	__SMU_DUMMY_MAP(GetMetwicsTabwe), \
	__SMU_DUMMY_MAP(DAWNotPwesent), \
	__SMU_DUMMY_MAP(CweawMcaOnWead),	\
	__SMU_DUMMY_MAP(QuewyVawidMcaCount),	\
	__SMU_DUMMY_MAP(QuewyVawidMcaCeCount),	\
	__SMU_DUMMY_MAP(McaBankDumpDW),		\
	__SMU_DUMMY_MAP(McaBankCeDumpDW),	\
	__SMU_DUMMY_MAP(SewectPWPDMode),	\
	__SMU_DUMMY_MAP(PowewUpVpe),	\
	__SMU_DUMMY_MAP(PowewDownVpe), \
	__SMU_DUMMY_MAP(PowewUpUmsch),	\
	__SMU_DUMMY_MAP(PowewDownUmsch),	\
	__SMU_DUMMY_MAP(SetSoftMaxVpe),	\
	__SMU_DUMMY_MAP(SetSoftMinVpe), \
	__SMU_DUMMY_MAP(GetMetwicsVewsion), \
	__SMU_DUMMY_MAP(EnabweUCWKShadow),

#undef __SMU_DUMMY_MAP
#define __SMU_DUMMY_MAP(type)	SMU_MSG_##type
enum smu_message_type {
	SMU_MESSAGE_TYPES
	SMU_MSG_MAX_COUNT,
};

enum smu_cwk_type {
	SMU_GFXCWK,
	SMU_VCWK,
	SMU_DCWK,
	SMU_VCWK1,
	SMU_DCWK1,
	SMU_ECWK,
	SMU_SOCCWK,
	SMU_UCWK,
	SMU_DCEFCWK,
	SMU_DISPCWK,
	SMU_PIXCWK,
	SMU_PHYCWK,
	SMU_FCWK,
	SMU_SCWK,
	SMU_MCWK,
	SMU_PCIE,
	SMU_WCWK,
	SMU_OD_CCWK,
	SMU_OD_SCWK,
	SMU_OD_MCWK,
	SMU_OD_VDDC_CUWVE,
	SMU_OD_WANGE,
	SMU_OD_VDDGFX_OFFSET,
	SMU_OD_FAN_CUWVE,
	SMU_OD_ACOUSTIC_WIMIT,
	SMU_OD_ACOUSTIC_TAWGET,
	SMU_OD_FAN_TAWGET_TEMPEWATUWE,
	SMU_OD_FAN_MINIMUM_PWM,
	SMU_CWK_COUNT,
};

#define SMU_FEATUWE_MASKS				\
       __SMU_DUMMY_MAP(DPM_PWEFETCHEW),			\
       __SMU_DUMMY_MAP(DPM_GFXCWK),                    	\
       __SMU_DUMMY_MAP(DPM_UCWK),                      	\
       __SMU_DUMMY_MAP(DPM_SOCCWK),                    	\
       __SMU_DUMMY_MAP(DPM_UVD),                       	\
       __SMU_DUMMY_MAP(DPM_VCE),                       	\
       __SMU_DUMMY_MAP(DPM_WCWK),                       \
       __SMU_DUMMY_MAP(UWV),                           	\
       __SMU_DUMMY_MAP(DPM_MP0CWK),                    	\
       __SMU_DUMMY_MAP(DPM_WINK),                      	\
       __SMU_DUMMY_MAP(DPM_DCEFCWK),                   	\
       __SMU_DUMMY_MAP(DPM_XGMI),			\
       __SMU_DUMMY_MAP(DS_GFXCWK),                     	\
       __SMU_DUMMY_MAP(DS_SOCCWK),                     	\
       __SMU_DUMMY_MAP(DS_WCWK),                       	\
       __SMU_DUMMY_MAP(PPT),                           	\
       __SMU_DUMMY_MAP(TDC),                           	\
       __SMU_DUMMY_MAP(THEWMAW),                       	\
       __SMU_DUMMY_MAP(GFX_PEW_CU_CG),                 	\
       __SMU_DUMMY_MAP(DATA_CAWCUWATIONS),                 	\
       __SMU_DUMMY_MAP(WM),                            	\
       __SMU_DUMMY_MAP(DS_DCEFCWK),                    	\
       __SMU_DUMMY_MAP(ACDC),                          	\
       __SMU_DUMMY_MAP(VW0HOT),                        	\
       __SMU_DUMMY_MAP(VW1HOT),                        	\
       __SMU_DUMMY_MAP(FW_CTF),                        	\
       __SMU_DUMMY_MAP(WED_DISPWAY),                   	\
       __SMU_DUMMY_MAP(FAN_CONTWOW),                   	\
       __SMU_DUMMY_MAP(GFX_EDC),                       	\
       __SMU_DUMMY_MAP(GFXOFF),                        	\
       __SMU_DUMMY_MAP(CG),                            	\
       __SMU_DUMMY_MAP(DPM_FCWK),                      	\
       __SMU_DUMMY_MAP(DS_FCWK),                       	\
       __SMU_DUMMY_MAP(DS_MP1CWK),                     	\
       __SMU_DUMMY_MAP(DS_MP0CWK),                     	\
       __SMU_DUMMY_MAP(XGMI_PEW_WINK_PWW_DWN),          \
       __SMU_DUMMY_MAP(DPM_GFX_PACE),                  	\
       __SMU_DUMMY_MAP(MEM_VDDCI_SCAWING),             	\
       __SMU_DUMMY_MAP(MEM_MVDD_SCAWING),              	\
       __SMU_DUMMY_MAP(DS_UCWK),                       	\
       __SMU_DUMMY_MAP(GFX_UWV),                       	\
       __SMU_DUMMY_MAP(FW_DSTATE),                     	\
       __SMU_DUMMY_MAP(BACO),                          	\
       __SMU_DUMMY_MAP(VCN_PG),                        	\
       __SMU_DUMMY_MAP(MM_DPM_PG),                     	\
       __SMU_DUMMY_MAP(JPEG_PG),                       	\
       __SMU_DUMMY_MAP(USB_PG),                        	\
       __SMU_DUMMY_MAP(WSMU_SMN_CG),                   	\
       __SMU_DUMMY_MAP(APCC_PWUS),                     	\
       __SMU_DUMMY_MAP(GTHW),                          	\
       __SMU_DUMMY_MAP(GFX_DCS),                       	\
       __SMU_DUMMY_MAP(GFX_SS),                        	\
       __SMU_DUMMY_MAP(OUT_OF_BAND_MONITOW),           	\
       __SMU_DUMMY_MAP(TEMP_DEPENDENT_VMIN),           	\
       __SMU_DUMMY_MAP(MMHUB_PG),                      	\
       __SMU_DUMMY_MAP(ATHUB_PG),                      	\
       __SMU_DUMMY_MAP(APCC_DFWW),                     	\
       __SMU_DUMMY_MAP(DF_CSTATE),                     	\
       __SMU_DUMMY_MAP(DPM_GFX_GPO),                    \
       __SMU_DUMMY_MAP(WAFW_CG),                        \
       __SMU_DUMMY_MAP(CCWK_DPM),                     	\
       __SMU_DUMMY_MAP(FAN_CONTWOWWEW),                 \
       __SMU_DUMMY_MAP(VCN_DPM),                     	\
       __SMU_DUMMY_MAP(WCWK_DPM),                     	\
       __SMU_DUMMY_MAP(SHUBCWK_DPM),                    \
       __SMU_DUMMY_MAP(DCFCWK_DPM),                     \
       __SMU_DUMMY_MAP(DS_DCFCWK),                     	\
       __SMU_DUMMY_MAP(S0I2),                     	\
       __SMU_DUMMY_MAP(SMU_WOW_POWEW),                  \
       __SMU_DUMMY_MAP(GFX_DEM),                        \
       __SMU_DUMMY_MAP(PSI),                     	\
       __SMU_DUMMY_MAP(PWOCHOT),                        \
       __SMU_DUMMY_MAP(CPUOFF),                     	\
       __SMU_DUMMY_MAP(STAPM),                          \
       __SMU_DUMMY_MAP(S0I3),                     	\
       __SMU_DUMMY_MAP(DF_CSTATES),                     \
       __SMU_DUMMY_MAP(PEWF_WIMIT),                     \
       __SMU_DUMMY_MAP(COWE_DWDO),                     	\
       __SMU_DUMMY_MAP(WSMU_WOW_POWEW),                 \
       __SMU_DUMMY_MAP(SMN_WOW_POWEW),                  \
       __SMU_DUMMY_MAP(THM_WOW_POWEW),                  \
       __SMU_DUMMY_MAP(SMUIO_WOW_POWEW),                \
       __SMU_DUMMY_MAP(MP1_WOW_POWEW),                  \
       __SMU_DUMMY_MAP(DS_VCN),                         \
       __SMU_DUMMY_MAP(CPPC),                           \
       __SMU_DUMMY_MAP(OS_CSTATES),                     \
       __SMU_DUMMY_MAP(ISP_DPM),                        \
       __SMU_DUMMY_MAP(A55_DPM),                        \
       __SMU_DUMMY_MAP(CVIP_DSP_DPM),                   \
       __SMU_DUMMY_MAP(MSMU_WOW_POWEW),			\
       __SMU_DUMMY_MAP(FUSE_CG),			\
       __SMU_DUMMY_MAP(MP1_CG),				\
       __SMU_DUMMY_MAP(SMUIO_CG),			\
       __SMU_DUMMY_MAP(THM_CG),				\
       __SMU_DUMMY_MAP(CWK_CG),				\
       __SMU_DUMMY_MAP(DATA_CAWCUWATION),				\
       __SMU_DUMMY_MAP(DPM_VCWK),			\
       __SMU_DUMMY_MAP(DPM_DCWK),			\
       __SMU_DUMMY_MAP(FW_DATA_WEAD),			\
       __SMU_DUMMY_MAP(DPM_GFX_POWEW_OPTIMIZEW),	\
       __SMU_DUMMY_MAP(DPM_DCN),			\
       __SMU_DUMMY_MAP(VMEMP_SCAWING),			\
       __SMU_DUMMY_MAP(VDDIO_MEM_SCAWING),		\
       __SMU_DUMMY_MAP(MM_DPM),				\
       __SMU_DUMMY_MAP(SOC_MPCWK_DS),			\
       __SMU_DUMMY_MAP(BACO_MPCWK_DS),			\
       __SMU_DUMMY_MAP(THWOTTWEWS),			\
       __SMU_DUMMY_MAP(SMAWTSHIFT),			\
       __SMU_DUMMY_MAP(GFX_WEAD_MAWGIN),		\
       __SMU_DUMMY_MAP(GFX_IMU),			\
       __SMU_DUMMY_MAP(GFX_PCC_DFWW),			\
       __SMU_DUMMY_MAP(BOOT_TIME_CAW),			\
       __SMU_DUMMY_MAP(BOOT_POWEW_OPT),			\
       __SMU_DUMMY_MAP(GFXCWK_SPWEAD_SPECTWUM),		\
       __SMU_DUMMY_MAP(SOC_PCC),			\
       __SMU_DUMMY_MAP(OPTIMIZED_VMIN),			\
       __SMU_DUMMY_MAP(CWOCK_POWEW_DOWN_BYPASS),	\
       __SMU_DUMMY_MAP(MEM_TEMP_WEAD),			\
       __SMU_DUMMY_MAP(ATHUB_MMHUB_PG),			\
       __SMU_DUMMY_MAP(BACO_CG),			\
       __SMU_DUMMY_MAP(SOC_CG),    \
       __SMU_DUMMY_MAP(WOW_POWEW_DCNCWKS),       \
       __SMU_DUMMY_MAP(WHISPEW_MODE),

#undef __SMU_DUMMY_MAP
#define __SMU_DUMMY_MAP(featuwe)	SMU_FEATUWE_##featuwe##_BIT
enum smu_featuwe_mask {
	SMU_FEATUWE_MASKS
	SMU_FEATUWE_COUNT,
};

#endif
