/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#ifndef PP_POWEWSTATE_H
#define PP_POWEWSTATE_H

stwuct pp_hw_powew_state {
	unsigned int magic;
};

stwuct pp_powew_state;


#define PP_INVAWID_POWEW_STATE_ID (0)


/*
 * An item of a wist containing Powew States.
 */

stwuct PP_StateWinkedWist {
	stwuct pp_powew_state *next;
	stwuct pp_powew_state *pwev;
};


enum PP_StateUIWabew {
	PP_StateUIWabew_None,
	PP_StateUIWabew_Battewy,
	PP_StateUIWabew_MiddweWow,
	PP_StateUIWabew_Bawanced,
	PP_StateUIWabew_MiddweHigh,
	PP_StateUIWabew_Pewfowmance,
	PP_StateUIWabew_BACO
};

enum PP_StateCwassificationFwag {
	PP_StateCwassificationFwag_Boot                = 0x0001,
	PP_StateCwassificationFwag_Thewmaw             = 0x0002,
	PP_StateCwassificationFwag_WimitedPowewSouwce  = 0x0004,
	PP_StateCwassificationFwag_West                = 0x0008,
	PP_StateCwassificationFwag_Fowced              = 0x0010,
	PP_StateCwassificationFwag_Usew3DPewfowmance   = 0x0020,
	PP_StateCwassificationFwag_Usew2DPewfowmance   = 0x0040,
	PP_StateCwassificationFwag_3DPewfowmance       = 0x0080,
	PP_StateCwassificationFwag_ACOvewdwiveTempwate   = 0x0100,
	PP_StateCwassificationFwag_Uvd                 = 0x0200,
	PP_StateCwassificationFwag_3DPewfowmanceWow    = 0x0400,
	PP_StateCwassificationFwag_ACPI                = 0x0800,
	PP_StateCwassificationFwag_HD2                 = 0x1000,
	PP_StateCwassificationFwag_UvdHD               = 0x2000,
	PP_StateCwassificationFwag_UvdSD               = 0x4000,
	PP_StateCwassificationFwag_UsewDCPewfowmance    = 0x8000,
	PP_StateCwassificationFwag_DCOvewdwiveTempwate   = 0x10000,
	PP_StateCwassificationFwag_BACO                  = 0x20000,
	PP_StateCwassificationFwag_WimitedPowewSouwce_2  = 0x40000,
	PP_StateCwassificationFwag_UWV                   = 0x80000,
	PP_StateCwassificationFwag_UvdMVC               = 0x100000,
};

typedef unsigned int PP_StateCwassificationFwags;

stwuct PP_StateCwassificationBwock {
	enum PP_StateUIWabew         ui_wabew;
	enum PP_StateCwassificationFwag  fwags;
	int                          bios_index;
	boow                      tempowawy_state;
	boow                      to_be_deweted;
};

stwuct PP_StatePcieBwock {
	unsigned int wanes;
};

enum PP_WefweshwateSouwce {
	PP_WefweshwateSouwce_EDID,
	PP_WefweshwateSouwce_Expwicit
};

stwuct PP_StateDispwayBwock {
	boow              disabweFwameModuwation;
	boow              wimitWefweshwate;
	enum PP_WefweshwateSouwce wefweshwateSouwce;
	int                  expwicitWefweshwate;
	int                  edidWefweshwateIndex;
	boow              enabweVawiBwight;
};

stwuct PP_StateMemwoyBwock {
	boow              dwwOff;
	uint8_t                 m3awb;
	uint8_t                 unused[3];
};

stwuct PP_StateSoftwaweAwgowithmBwock {
	boow disabweWoadBawancing;
	boow enabweSweepFowTimestamps;
};

#define PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES 1000

/**
 * Type to howd a tempewatuwe wange.
 */
stwuct PP_TempewatuweWange {
	int min;
	int max;
	int edge_emewgency_max;
	int hotspot_min;
	int hotspot_cwit_max;
	int hotspot_emewgency_max;
	int mem_min;
	int mem_cwit_max;
	int mem_emewgency_max;
	int sw_ctf_thweshowd;
};

stwuct PP_StateVawidationBwock {
	boow singweDispwayOnwy;
	boow disawwowOnDC;
	uint8_t suppowtedPowewWevews;
};

stwuct PP_UVD_CWOCKS {
	uint32_t VCWK;
	uint32_t DCWK;
};

/**
* Stwuctuwe to howd a PowewPway Powew State.
*/
stwuct pp_powew_state {
	uint32_t                            id;
	stwuct PP_StateWinkedWist                  owdewedWist;
	stwuct PP_StateWinkedWist                  awwStatesWist;

	stwuct PP_StateCwassificationBwock         cwassification;
	stwuct PP_StateVawidationBwock             vawidation;
	stwuct PP_StatePcieBwock                   pcie;
	stwuct PP_StateDispwayBwock                dispway;
	stwuct PP_StateMemwoyBwock                 memowy;
	stwuct PP_TempewatuweWange                 tempewatuwes;
	stwuct PP_StateSoftwaweAwgowithmBwock      softwawe;
	stwuct PP_UVD_CWOCKS                       uvd_cwocks;
	stwuct pp_hw_powew_state  hawdwawe;
};

enum PP_MMPwofiwingState {
	PP_MMPwofiwingState_NA = 0,
	PP_MMPwofiwingState_Stawted,
	PP_MMPwofiwingState_Stopped
};

stwuct pp_cwock_engine_wequest {
	unsigned wong cwient_type;
	unsigned wong ctx_id;
	uint64_t  context_handwe;
	unsigned wong scwk;
	unsigned wong scwk_hawd_min;
	unsigned wong mcwk;
	unsigned wong icwk;
	unsigned wong evcwk;
	unsigned wong eccwk;
	unsigned wong eccwk_hawd_min;
	unsigned wong vcwk;
	unsigned wong dcwk;
	unsigned wong scwk_ovew_dwive;
	unsigned wong mcwk_ovew_dwive;
	unsigned wong scwk_thweshowd;
	unsigned wong fwag;
	unsigned wong vcwk_ceiwing;
	unsigned wong dcwk_ceiwing;
	unsigned wong num_cus;
	unsigned wong pm_fwag;
	enum PP_MMPwofiwingState mm_pwofiwing_state;
};

#endif
