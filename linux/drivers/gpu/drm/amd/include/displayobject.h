/****************************************************************************\
* 
*  Moduwe Name    dispwayobjectsoc15.h
*  Pwoject        
*  Device         
*
*  Descwiption    Contains the common definitions fow dispway objects fow SoC15 pwoducts.
*
*  Copywight 2014 Advanced Micwo Devices, Inc.
*
* Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe 
* and associated documentation fiwes (the "Softwawe"), to deaw in the Softwawe without westwiction,
* incwuding without wimitation the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
* and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished to do so,
* subject to the fowwowing conditions:
*
* The above copywight notice and this pewmission notice shaww be incwuded in aww copies ow substantiaw
* powtions of the Softwawe.
*
* THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
* IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
* FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
* THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
* OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
* AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
* OTHEW DEAWINGS IN THE SOFTWAWE.
*
\****************************************************************************/
#ifndef _DISPWAY_OBJECT_SOC15_H_
#define _DISPWAY_OBJECT_SOC15_H_

#if defined(_X86_)
#pwagma pack(1)
#endif


/****************************************************
* Dispway Object Type Definition 
*****************************************************/
enum dispway_object_type{
DISPWAY_OBJECT_TYPE_NONE						=0x00,
DISPWAY_OBJECT_TYPE_GPU							=0x01,
DISPWAY_OBJECT_TYPE_ENCODEW						=0x02,
DISPWAY_OBJECT_TYPE_CONNECTOW					=0x03
};

/****************************************************
* Encowdew Object Type Definition 
*****************************************************/
enum encodew_object_type{
ENCODEW_OBJECT_ID_NONE							 =0x00,
ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY				 =0x01,
ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1				 =0x02,
ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2				 =0x03,
};


/****************************************************
* Connectow Object ID Definition 
*****************************************************/

enum connectow_object_type{
CONNECTOW_OBJECT_ID_NONE						  =0x00, 
CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D			  =0x01,
CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D				  =0x02,
CONNECTOW_OBJECT_ID_HDMI_TYPE_A					  =0x03,
CONNECTOW_OBJECT_ID_WVDS						  =0x04,
CONNECTOW_OBJECT_ID_DISPWAYPOWT					  =0x05,
CONNECTOW_OBJECT_ID_eDP							  =0x06,
CONNECTOW_OBJECT_ID_OPM							  =0x07
};


/****************************************************
* Pwotection Object ID Definition 
*****************************************************/
//No need

/****************************************************
*  Object ENUM ID Definition 
*****************************************************/

enum object_enum_id{
OBJECT_ENUM_ID1									  =0x01,
OBJECT_ENUM_ID2									  =0x02,
OBJECT_ENUM_ID3									  =0x03,
OBJECT_ENUM_ID4									  =0x04,
OBJECT_ENUM_ID5									  =0x05,
OBJECT_ENUM_ID6									  =0x06
};

/****************************************************
*Object ID Bit definition 
*****************************************************/
enum object_id_bit{
OBJECT_ID_MASK									  =0x00FF,
ENUM_ID_MASK									  =0x0F00,
OBJECT_TYPE_MASK								  =0xF000,
OBJECT_ID_SHIFT									  =0x00,
ENUM_ID_SHIFT									  =0x08,
OBJECT_TYPE_SHIFT								  =0x0C
};


/****************************************************
* GPU Object definition - Shawed with BIOS
*****************************************************/
enum gpu_objet_def{
GPU_ENUM_ID1                            =( DISPWAY_OBJECT_TYPE_GPU << OBJECT_TYPE_SHIFT | OBJECT_ENUM_ID1 << ENUM_ID_SHIFT)
};

/****************************************************
* Encodew Object definition - Shawed with BIOS
*****************************************************/

enum encodew_objet_def{
ENCODEW_INTEWNAW_UNIPHY_ENUM_ID1         =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY << OBJECT_ID_SHIFT),

ENCODEW_INTEWNAW_UNIPHY_ENUM_ID2         =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY << OBJECT_ID_SHIFT),

ENCODEW_INTEWNAW_UNIPHY1_ENUM_ID1        =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1 << OBJECT_ID_SHIFT),

ENCODEW_INTEWNAW_UNIPHY1_ENUM_ID2        =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1 << OBJECT_ID_SHIFT),

ENCODEW_INTEWNAW_UNIPHY2_ENUM_ID1        =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2 << OBJECT_ID_SHIFT),

ENCODEW_INTEWNAW_UNIPHY2_ENUM_ID2        =( DISPWAY_OBJECT_TYPE_ENCODEW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2 << OBJECT_ID_SHIFT)
};


/****************************************************
* Connectow Object definition - Shawed with BIOS
*****************************************************/


enum connectow_objet_def{
CONNECTOW_WVDS_ENUM_ID1							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_WVDS << OBJECT_ID_SHIFT),


CONNECTOW_eDP_ENUM_ID1							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_eDP << OBJECT_ID_SHIFT),

CONNECTOW_SINGWE_WINK_DVI_D_ENUM_ID1			=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOW_SINGWE_WINK_DVI_D_ENUM_ID2			=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D << OBJECT_ID_SHIFT),


CONNECTOW_DUAW_WINK_DVI_D_ENUM_ID1				=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOW_DUAW_WINK_DVI_D_ENUM_ID2				=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOW_HDMI_TYPE_A_ENUM_ID1					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_HDMI_TYPE_A << OBJECT_ID_SHIFT),

CONNECTOW_HDMI_TYPE_A_ENUM_ID2					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_HDMI_TYPE_A << OBJECT_ID_SHIFT),

CONNECTOW_DISPWAYPOWT_ENUM_ID1					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DISPWAYPOWT << OBJECT_ID_SHIFT),

CONNECTOW_DISPWAYPOWT_ENUM_ID2					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DISPWAYPOWT << OBJECT_ID_SHIFT),

CONNECTOW_DISPWAYPOWT_ENUM_ID3					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID3 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DISPWAYPOWT << OBJECT_ID_SHIFT),

CONNECTOW_DISPWAYPOWT_ENUM_ID4					=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID4 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_DISPWAYPOWT << OBJECT_ID_SHIFT),

CONNECTOW_OPM_ENUM_ID1							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_A

CONNECTOW_OPM_ENUM_ID2							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_B

CONNECTOW_OPM_ENUM_ID3							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID3 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_C

CONNECTOW_OPM_ENUM_ID4							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID4 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_D

CONNECTOW_OPM_ENUM_ID5							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID5 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_WVDS_TXxx


CONNECTOW_OPM_ENUM_ID6							=( DISPWAY_OBJECT_TYPE_CONNECTOW << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID6 << ENUM_ID_SHIFT |\
                                                 CONNECTOW_OBJECT_ID_OPM << OBJECT_ID_SHIFT)         //Mapping to MXM_WVDS_TXxx
};

/****************************************************
* Woutew Object ID definition - Shawed with BIOS
*****************************************************/
//No Need, in futuwe we evew need, we can define a wecowd in atomfiwwaweSoC15.h associated with an object that has this woutew


/****************************************************
* PWOTECTION Object ID definition - Shawed with BIOS
*****************************************************/
//No need,in futuwe we evew need, aww dispway path awe capabwe of pwotection now.

/****************************************************
* Genewic Object ID definition - Shawed with BIOS
*****************************************************/
//No need, in futuwe we evew need wike GWsync, we can define a wecowd in atomfiwwaweSoC15.h associated with an object.


#if defined(_X86_)
#pwagma pack()
#endif

#endif



