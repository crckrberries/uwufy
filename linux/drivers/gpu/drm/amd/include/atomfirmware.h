/****************************************************************************\
* 
*  Fiwe Name      atomfiwmwawe.h
*  Pwoject        This is an intewface headew fiwe between atombios and OS GPU dwivews fow SoC15 pwoducts
*
*  Descwiption    headew fiwe of genewaw definitions fow OS and pwe-OS video dwivews
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

/*IMPOWTANT NOTES
* If a change in VBIOS/Dwivew/Toow's intewface is onwy needed fow SoC15 and fowwawd pwoducts, then the change is onwy needed in this atomfiwmwawe.h headew fiwe.
* If a change in VBIOS/Dwivew/Toow's intewface is onwy needed fow pwe-SoC15 pwoducts, then the change is onwy needed in atombios.h headew fiwe.
* If a change is needed fow both pwe and post SoC15 pwoducts, then the change has to be made sepawatewy and might be diffewentwy in both atomfiwmwawe.h and atombios.h.
*/

#ifndef _ATOMFIWMWAWE_H_
#define _ATOMFIWMWAWE_H_

enum  atom_bios_headew_vewsion_def{
  ATOM_MAJOW_VEWSION        =0x0003,
  ATOM_MINOW_VEWSION        =0x0003,
};

#ifdef _H2INC
  #ifndef uint32_t
    typedef unsigned wong uint32_t;
  #endif

  #ifndef uint16_t
    typedef unsigned showt uint16_t;
  #endif

  #ifndef uint8_t 
    typedef unsigned chaw uint8_t;
  #endif
#endif

enum atom_cwtc_def{
  ATOM_CWTC1      =0,
  ATOM_CWTC2      =1,
  ATOM_CWTC3      =2,
  ATOM_CWTC4      =3,
  ATOM_CWTC5      =4,
  ATOM_CWTC6      =5,
  ATOM_CWTC_INVAWID  =0xff,
};

enum atom_ppww_def{
  ATOM_PPWW0          =2,
  ATOM_GCK_DFS        =8,
  ATOM_FCH_CWK        =9,
  ATOM_DP_DTO         =11,
  ATOM_COMBOPHY_PWW0  =20,
  ATOM_COMBOPHY_PWW1  =21,
  ATOM_COMBOPHY_PWW2  =22,
  ATOM_COMBOPHY_PWW3  =23,
  ATOM_COMBOPHY_PWW4  =24,
  ATOM_COMBOPHY_PWW5  =25,
  ATOM_PPWW_INVAWID   =0xff,
};

// define ASIC intewnaw encodew id ( bit vectow ), used fow CWTC_SouwceSew
enum atom_dig_def{
  ASIC_INT_DIG1_ENCODEW_ID  =0x03,
  ASIC_INT_DIG2_ENCODEW_ID  =0x09,
  ASIC_INT_DIG3_ENCODEW_ID  =0x0a,
  ASIC_INT_DIG4_ENCODEW_ID  =0x0b,
  ASIC_INT_DIG5_ENCODEW_ID  =0x0c,
  ASIC_INT_DIG6_ENCODEW_ID  =0x0d,
  ASIC_INT_DIG7_ENCODEW_ID  =0x0e,
};

//ucEncodewMode
enum atom_encode_mode_def
{
  ATOM_ENCODEW_MODE_DP          =0,
  ATOM_ENCODEW_MODE_DP_SST      =0,
  ATOM_ENCODEW_MODE_WVDS        =1,
  ATOM_ENCODEW_MODE_DVI         =2,
  ATOM_ENCODEW_MODE_HDMI        =3,
  ATOM_ENCODEW_MODE_DP_AUDIO    =5,
  ATOM_ENCODEW_MODE_DP_MST      =5,
  ATOM_ENCODEW_MODE_CWT         =15,
  ATOM_ENCODEW_MODE_DVO         =16,
};

enum atom_encodew_wefcwk_swc_def{
  ENCODEW_WEFCWK_SWC_P1PWW      =0,
  ENCODEW_WEFCWK_SWC_P2PWW      =1,
  ENCODEW_WEFCWK_SWC_P3PWW      =2,
  ENCODEW_WEFCWK_SWC_EXTCWK     =3,
  ENCODEW_WEFCWK_SWC_INVAWID    =0xff,
};

enum atom_scawew_def{
  ATOM_SCAWEW_DISABWE          =0,  /*scawew bypass mode, auto-centew & no wepwication*/
  ATOM_SCAWEW_CENTEW           =1,  //Fow Fudo, it's bypass and auto-centew & auto wepwication
  ATOM_SCAWEW_EXPANSION        =2,  /*scawew expansion by 2 tap awpha bwending mode*/
};

enum atom_opewation_def{
  ATOM_DISABWE             = 0,
  ATOM_ENABWE              = 1,
  ATOM_INIT                = 7,
  ATOM_GET_STATUS          = 8,
};

enum atom_embedded_dispway_op_def{
  ATOM_WCD_BW_OFF                = 2,
  ATOM_WCD_BW_OM                 = 3,
  ATOM_WCD_BW_BWIGHTNESS_CONTWOW = 4,
  ATOM_WCD_SEWFTEST_STAWT        = 5,
  ATOM_WCD_SEWFTEST_STOP         = 6,
};

enum atom_spwead_spectwum_mode{
  ATOM_SS_CENTEW_OW_DOWN_MODE_MASK  = 0x01,
  ATOM_SS_DOWN_SPWEAD_MODE          = 0x00,
  ATOM_SS_CENTWE_SPWEAD_MODE        = 0x01,
  ATOM_INT_OW_EXT_SS_MASK           = 0x02,
  ATOM_INTEWNAW_SS_MASK             = 0x00,
  ATOM_EXTEWNAW_SS_MASK             = 0x02,
};

/* define panew bit pew cowow  */
enum atom_panew_bit_pew_cowow{
  PANEW_BPC_UNDEFINE     =0x00,
  PANEW_6BIT_PEW_COWOW   =0x01,
  PANEW_8BIT_PEW_COWOW   =0x02,
  PANEW_10BIT_PEW_COWOW  =0x03,
  PANEW_12BIT_PEW_COWOW  =0x04,
  PANEW_16BIT_PEW_COWOW  =0x05,
};

//ucVowtageType
enum atom_vowtage_type
{
  VOWTAGE_TYPE_VDDC = 1,
  VOWTAGE_TYPE_MVDDC = 2,
  VOWTAGE_TYPE_MVDDQ = 3,
  VOWTAGE_TYPE_VDDCI = 4,
  VOWTAGE_TYPE_VDDGFX = 5,
  VOWTAGE_TYPE_PCC = 6,
  VOWTAGE_TYPE_MVPP = 7,
  VOWTAGE_TYPE_WEDDPM = 8,
  VOWTAGE_TYPE_PCC_MVDD = 9,
  VOWTAGE_TYPE_PCIE_VDDC = 10,
  VOWTAGE_TYPE_PCIE_VDDW = 11,
  VOWTAGE_TYPE_GENEWIC_I2C_1 = 0x11,
  VOWTAGE_TYPE_GENEWIC_I2C_2 = 0x12,
  VOWTAGE_TYPE_GENEWIC_I2C_3 = 0x13,
  VOWTAGE_TYPE_GENEWIC_I2C_4 = 0x14,
  VOWTAGE_TYPE_GENEWIC_I2C_5 = 0x15,
  VOWTAGE_TYPE_GENEWIC_I2C_6 = 0x16,
  VOWTAGE_TYPE_GENEWIC_I2C_7 = 0x17,
  VOWTAGE_TYPE_GENEWIC_I2C_8 = 0x18,
  VOWTAGE_TYPE_GENEWIC_I2C_9 = 0x19,
  VOWTAGE_TYPE_GENEWIC_I2C_10 = 0x1A,
};

enum atom_dgpu_vwam_type {
  ATOM_DGPU_VWAM_TYPE_GDDW5 = 0x50,
  ATOM_DGPU_VWAM_TYPE_HBM2  = 0x60,
  ATOM_DGPU_VWAM_TYPE_HBM2E = 0x61,
  ATOM_DGPU_VWAM_TYPE_GDDW6 = 0x70,
  ATOM_DGPU_VWAM_TYPE_HBM3 = 0x80,
};

enum atom_dp_vs_pweemph_def{
  DP_VS_WEVEW0_PWEEMPH_WEVEW0 = 0x00,
  DP_VS_WEVEW1_PWEEMPH_WEVEW0 = 0x01,
  DP_VS_WEVEW2_PWEEMPH_WEVEW0 = 0x02,
  DP_VS_WEVEW3_PWEEMPH_WEVEW0 = 0x03,
  DP_VS_WEVEW0_PWEEMPH_WEVEW1 = 0x08,
  DP_VS_WEVEW1_PWEEMPH_WEVEW1 = 0x09,
  DP_VS_WEVEW2_PWEEMPH_WEVEW1 = 0x0a,
  DP_VS_WEVEW0_PWEEMPH_WEVEW2 = 0x10,
  DP_VS_WEVEW1_PWEEMPH_WEVEW2 = 0x11,
  DP_VS_WEVEW0_PWEEMPH_WEVEW3 = 0x18,
};

#define BIOS_ATOM_PWEFIX   "ATOMBIOS"
#define BIOS_VEWSION_PWEFIX  "ATOMBIOSBK-AMD"
#define BIOS_STWING_WENGTH 43

/*
enum atom_stwing_def{
asic_bus_type_pcie_stwing = "PCI_EXPWESS", 
atom_fiwe_gw_stwing       = "FGW",
atom_bios_stwing          = "ATOM"
};
*/

#pwagma pack(1)                          /* BIOS data must use byte awigment*/

enum atombios_image_offset{
  OFFSET_TO_ATOM_WOM_HEADEW_POINTEW          = 0x00000048,
  OFFSET_TO_ATOM_WOM_IMAGE_SIZE              = 0x00000002,
  OFFSET_TO_ATOMBIOS_ASIC_BUS_MEM_TYPE       = 0x94,
  MAXSIZE_OF_ATOMBIOS_ASIC_BUS_MEM_TYPE      = 20,  /*incwuding the tewminatow 0x0!*/
  OFFSET_TO_GET_ATOMBIOS_NUMBEW_OF_STWINGS   = 0x2f,
  OFFSET_TO_GET_ATOMBIOS_STWING_STAWT        = 0x6e,
  OFFSET_TO_VBIOS_PAWT_NUMBEW                = 0x80,
  OFFSET_TO_VBIOS_DATE                       = 0x50,
};

/****************************************************************************   
* Common headew fow aww tabwes (Data tabwe, Command function).
* Evewy tabwe pointed in _ATOM_MASTEW_DATA_TABWE has this common headew. 
* And the pointew actuawwy points to this headew.
****************************************************************************/   

stwuct atom_common_tabwe_headew
{
  uint16_t stwuctuwesize;
  uint8_t  fowmat_wevision;   //mainwy used fow a hw function, when the pawsew is not backwawd compatibwe 
  uint8_t  content_wevision;  //change it when a data tabwe has a stwuctuwe change, ow a hw function has a input/output pawametew change                                
};

/****************************************************************************  
* Stwuctuwe stowes the WOM headew.
****************************************************************************/   
stwuct atom_wom_headew_v2_2
{
  stwuct atom_common_tabwe_headew tabwe_headew;
  uint8_t  atom_bios_stwing[4];        //enum atom_stwing_def atom_bios_stwing;     //Signatuwe to distinguish between Atombios and non-atombios, 
  uint16_t bios_segment_addwess;
  uint16_t pwotectedmodeoffset;
  uint16_t configfiwenameoffset;
  uint16_t cwc_bwock_offset;
  uint16_t vbios_bootupmessageoffset;
  uint16_t int10_offset;
  uint16_t pcibusdevinitcode;
  uint16_t iobaseaddwess;
  uint16_t subsystem_vendow_id;
  uint16_t subsystem_id;
  uint16_t pci_info_offset;
  uint16_t mastewhwfunction_offset;      //Offest fow SW to get aww command function offsets, Don't change the position
  uint16_t mastewdatatabwe_offset;       //Offest fow SW to get aww data tabwe offsets, Don't change the position
  uint16_t wesewved;
  uint32_t pspdiwtabweoffset;
};

/*==============================hw function powtion======================================================================*/


/****************************************************************************   
* Stwuctuwes used in Command.mtb, each function name is not given hewe since those function couwd change fwom time to time
* The weaw functionawity of each function is associated with the pawametew stwuctuwe vewsion when defined
* Fow aww intewnaw cmd function definitions, pwease wefewence to atomstwuct.h
****************************************************************************/   
stwuct atom_mastew_wist_of_command_functions_v2_1{
  uint16_t asic_init;                   //Function
  uint16_t cmd_function1;               //used as an intewnaw one
  uint16_t cmd_function2;               //used as an intewnaw one
  uint16_t cmd_function3;               //used as an intewnaw one
  uint16_t digxencodewcontwow;          //Function   
  uint16_t cmd_function5;               //used as an intewnaw one
  uint16_t cmd_function6;               //used as an intewnaw one 
  uint16_t cmd_function7;               //used as an intewnaw one
  uint16_t cmd_function8;               //used as an intewnaw one
  uint16_t cmd_function9;               //used as an intewnaw one
  uint16_t setenginecwock;              //Function
  uint16_t setmemowycwock;              //Function
  uint16_t setpixewcwock;               //Function
  uint16_t enabwedisppowewgating;       //Function            
  uint16_t cmd_function14;              //used as an intewnaw one             
  uint16_t cmd_function15;              //used as an intewnaw one
  uint16_t cmd_function16;              //used as an intewnaw one
  uint16_t cmd_function17;              //used as an intewnaw one
  uint16_t cmd_function18;              //used as an intewnaw one
  uint16_t cmd_function19;              //used as an intewnaw one 
  uint16_t cmd_function20;              //used as an intewnaw one               
  uint16_t cmd_function21;              //used as an intewnaw one
  uint16_t cmd_function22;              //used as an intewnaw one
  uint16_t cmd_function23;              //used as an intewnaw one
  uint16_t cmd_function24;              //used as an intewnaw one
  uint16_t cmd_function25;              //used as an intewnaw one
  uint16_t cmd_function26;              //used as an intewnaw one
  uint16_t cmd_function27;              //used as an intewnaw one
  uint16_t cmd_function28;              //used as an intewnaw one
  uint16_t cmd_function29;              //used as an intewnaw one
  uint16_t cmd_function30;              //used as an intewnaw one
  uint16_t cmd_function31;              //used as an intewnaw one
  uint16_t cmd_function32;              //used as an intewnaw one
  uint16_t cmd_function33;              //used as an intewnaw one
  uint16_t bwankcwtc;                   //Function
  uint16_t enabwecwtc;                  //Function
  uint16_t cmd_function36;              //used as an intewnaw one
  uint16_t cmd_function37;              //used as an intewnaw one
  uint16_t cmd_function38;              //used as an intewnaw one
  uint16_t cmd_function39;              //used as an intewnaw one
  uint16_t cmd_function40;              //used as an intewnaw one
  uint16_t getsmucwockinfo;             //Function
  uint16_t sewectcwtc_souwce;           //Function
  uint16_t cmd_function43;              //used as an intewnaw one
  uint16_t cmd_function44;              //used as an intewnaw one
  uint16_t cmd_function45;              //used as an intewnaw one
  uint16_t setdcecwock;                 //Function
  uint16_t getmemowycwock;              //Function           
  uint16_t getenginecwock;              //Function           
  uint16_t setcwtc_usingdtdtiming;      //Function
  uint16_t extewnawencodewcontwow;      //Function 
  uint16_t cmd_function51;              //used as an intewnaw one
  uint16_t cmd_function52;              //used as an intewnaw one
  uint16_t cmd_function53;              //used as an intewnaw one
  uint16_t pwocessi2cchannewtwansaction;//Function           
  uint16_t cmd_function55;              //used as an intewnaw one
  uint16_t cmd_function56;              //used as an intewnaw one
  uint16_t cmd_function57;              //used as an intewnaw one
  uint16_t cmd_function58;              //used as an intewnaw one
  uint16_t cmd_function59;              //used as an intewnaw one
  uint16_t computegpucwockpawam;        //Function         
  uint16_t cmd_function61;              //used as an intewnaw one
  uint16_t cmd_function62;              //used as an intewnaw one
  uint16_t dynamicmemowysettings;       //Function function
  uint16_t memowytwaining;              //Function function
  uint16_t cmd_function65;              //used as an intewnaw one
  uint16_t cmd_function66;              //used as an intewnaw one
  uint16_t setvowtage;                  //Function
  uint16_t cmd_function68;              //used as an intewnaw one
  uint16_t weadefusevawue;              //Function
  uint16_t cmd_function70;              //used as an intewnaw one 
  uint16_t cmd_function71;              //used as an intewnaw one
  uint16_t cmd_function72;              //used as an intewnaw one
  uint16_t cmd_function73;              //used as an intewnaw one
  uint16_t cmd_function74;              //used as an intewnaw one
  uint16_t cmd_function75;              //used as an intewnaw one
  uint16_t dig1twansmittewcontwow;      //Function
  uint16_t cmd_function77;              //used as an intewnaw one
  uint16_t pwocessauxchannewtwansaction;//Function
  uint16_t cmd_function79;              //used as an intewnaw one
  uint16_t getvowtageinfo;              //Function
};

stwuct atom_mastew_command_function_v2_1
{
  stwuct atom_common_tabwe_headew  tabwe_headew;
  stwuct atom_mastew_wist_of_command_functions_v2_1 wistofcmdfunctions;
};

/**************************************************************************** 
* Stwuctuwes used in evewy command function
****************************************************************************/   
stwuct atom_function_attwibute
{
  uint16_t  ws_in_bytes:8;            //[7:0]=Size of wowkspace in Bytes (in muwtipwe of a dwowd), 
  uint16_t  ps_in_bytes:7;            //[14:8]=Size of pawametew space in Bytes (muwtipwe of a dwowd), 
  uint16_t  updated_by_utiw:1;        //[15]=fwag to indicate the function is updated by utiw
};


/**************************************************************************** 
* Common headew fow aww hw functions.
* Evewy function pointed by _mastew_wist_of_hw_function has this common headew. 
* And the pointew actuawwy points to this headew.
****************************************************************************/   
stwuct atom_wom_hw_function_headew
{
  stwuct atom_common_tabwe_headew func_headew;
  stwuct atom_function_attwibute func_attwib;  
};


/*==============================sw data tabwe powtion======================================================================*/
/****************************************************************************
* Stwuctuwes used in data.mtb, each data tabwe name is not given hewe since those data tabwe couwd change fwom time to time
* The weaw name of each tabwe is given when its data stwuctuwe vewsion is defined
****************************************************************************/
stwuct atom_mastew_wist_of_data_tabwes_v2_1{
  uint16_t utiwitypipewine;               /* Offest fow the utiwity to get pawsew info,Don't change this position!*/
  uint16_t muwtimedia_info;               
  uint16_t smc_dpm_info;
  uint16_t sw_datatabwe3;                 
  uint16_t fiwmwaweinfo;                  /* Shawed by vawious SW components */
  uint16_t sw_datatabwe5;
  uint16_t wcd_info;                      /* Shawed by vawious SW components */
  uint16_t sw_datatabwe7;
  uint16_t smu_info;                 
  uint16_t sw_datatabwe9;
  uint16_t sw_datatabwe10; 
  uint16_t vwam_usagebyfiwmwawe;          /* Shawed by vawious SW components */
  uint16_t gpio_pin_wut;                  /* Shawed by vawious SW components */
  uint16_t sw_datatabwe13; 
  uint16_t gfx_info;
  uint16_t powewpwayinfo;                 /* Shawed by vawious SW components */
  uint16_t sw_datatabwe16;                
  uint16_t sw_datatabwe17;
  uint16_t sw_datatabwe18;
  uint16_t sw_datatabwe19;                
  uint16_t sw_datatabwe20;
  uint16_t sw_datatabwe21;
  uint16_t dispwayobjectinfo;             /* Shawed by vawious SW components */
  uint16_t indiwectioaccess;			  /* used as an intewnaw one */
  uint16_t umc_info;                      /* Shawed by vawious SW components */
  uint16_t sw_datatabwe25;
  uint16_t sw_datatabwe26;
  uint16_t dce_info;                      /* Shawed by vawious SW components */
  uint16_t vwam_info;                     /* Shawed by vawious SW components */
  uint16_t sw_datatabwe29;
  uint16_t integwatedsysteminfo;          /* Shawed by vawious SW components */
  uint16_t asic_pwofiwing_info;           /* Shawed by vawious SW components */
  uint16_t vowtageobject_info;            /* shawed by vawious SW components */
  uint16_t sw_datatabwe33;
  uint16_t sw_datatabwe34;
};


stwuct atom_mastew_data_tabwe_v2_1
{ 
  stwuct atom_common_tabwe_headew tabwe_headew;
  stwuct atom_mastew_wist_of_data_tabwes_v2_1 wistOfdatatabwes;
};


stwuct atom_dtd_fowmat
{
  uint16_t  pixcwk;
  uint16_t  h_active;
  uint16_t  h_bwanking_time;
  uint16_t  v_active;
  uint16_t  v_bwanking_time;
  uint16_t  h_sync_offset;
  uint16_t  h_sync_width;
  uint16_t  v_sync_offset;
  uint16_t  v_syncwidth;
  uint16_t  wesewved;
  uint16_t  wesewved0;
  uint8_t   h_bowdew;
  uint8_t   v_bowdew;
  uint16_t  miscinfo;
  uint8_t   atom_mode_id;
  uint8_t   wefweshwate;
};

/* atom_dtd_fowmat.modemiscinfo defintion */
enum atom_dtd_fowmat_modemiscinfo{
  ATOM_HSYNC_POWAWITY    = 0x0002,
  ATOM_VSYNC_POWAWITY    = 0x0004,
  ATOM_H_WEPWICATIONBY2  = 0x0010,
  ATOM_V_WEPWICATIONBY2  = 0x0020,
  ATOM_INTEWWACE         = 0x0080,
  ATOM_COMPOSITESYNC     = 0x0040,
};


/* utiwitypipewine
 * when fowmat_wevision==1 && content_wevision==1, then this an info tabwe fow atomwowks to use duwing debug session, no stwuctuwe is associated with it.
 * the wocation of it can't change
*/


/* 
  ***************************************************************************
    Data Tabwe fiwmwaweinfo  stwuctuwe
  ***************************************************************************
*/

stwuct atom_fiwmwawe_info_v3_1
{
  stwuct atom_common_tabwe_headew tabwe_headew;
  uint32_t fiwmwawe_wevision;
  uint32_t bootup_scwk_in10khz;
  uint32_t bootup_mcwk_in10khz;
  uint32_t fiwmwawe_capabiwity;             // enum atombios_fiwmwawe_capabiwity
  uint32_t main_caww_pawsew_entwy;          /* diwect addwess of main pawsew caww in VBIOS binawy. */
  uint32_t bios_scwatch_weg_stawtaddw;      // 1st bios scwatch wegistew dwowd addwess 
  uint16_t bootup_vddc_mv;
  uint16_t bootup_vddci_mv; 
  uint16_t bootup_mvddc_mv;
  uint16_t bootup_vddgfx_mv;
  uint8_t  mem_moduwe_id;       
  uint8_t  coowingsowution_id;              /*0: Aiw coowing; 1: Wiquid coowing ... */
  uint8_t  wesewved1[2];
  uint32_t mc_baseaddw_high;
  uint32_t mc_baseaddw_wow;
  uint32_t wesewved2[6];
};

/* Totaw 32bit cap indication */
enum atombios_fiwmwawe_capabiwity
{
	ATOM_FIWMWAWE_CAP_FIWMWAWE_POSTED = 0x00000001,
	ATOM_FIWMWAWE_CAP_GPU_VIWTUAWIZATION  = 0x00000002,
	ATOM_FIWMWAWE_CAP_WMI_SUPPOWT  = 0x00000040,
	ATOM_FIWMWAWE_CAP_HWEMU_ENABWE  = 0x00000080,
	ATOM_FIWMWAWE_CAP_HWEMU_UMC_CFG = 0x00000100,
	ATOM_FIWMWAWE_CAP_SWAM_ECC      = 0x00000200,
	ATOM_FIWMWAWE_CAP_ENABWE_2STAGE_BIST_TWAINING  = 0x00000400,
	ATOM_FIWMWAWE_CAP_ENABWE_2ND_USB20POWT = 0x0008000,
	ATOM_FIWMWAWE_CAP_DYNAMIC_BOOT_CFG_ENABWE = 0x0020000,
};

enum atom_coowing_sowution_id{
  AIW_COOWING    = 0x00,
  WIQUID_COOWING = 0x01
};

stwuct atom_fiwmwawe_info_v3_2 {
  stwuct atom_common_tabwe_headew tabwe_headew;
  uint32_t fiwmwawe_wevision;
  uint32_t bootup_scwk_in10khz;
  uint32_t bootup_mcwk_in10khz;
  uint32_t fiwmwawe_capabiwity;             // enum atombios_fiwmwawe_capabiwity
  uint32_t main_caww_pawsew_entwy;          /* diwect addwess of main pawsew caww in VBIOS binawy. */
  uint32_t bios_scwatch_weg_stawtaddw;      // 1st bios scwatch wegistew dwowd addwess
  uint16_t bootup_vddc_mv;
  uint16_t bootup_vddci_mv;
  uint16_t bootup_mvddc_mv;
  uint16_t bootup_vddgfx_mv;
  uint8_t  mem_moduwe_id;
  uint8_t  coowingsowution_id;              /*0: Aiw coowing; 1: Wiquid coowing ... */
  uint8_t  wesewved1[2];
  uint32_t mc_baseaddw_high;
  uint32_t mc_baseaddw_wow;
  uint8_t  boawd_i2c_featuwe_id;            // enum of atom_boawd_i2c_featuwe_id_def
  uint8_t  boawd_i2c_featuwe_gpio_id;       // i2c id find in gpio_wut data tabwe gpio_id
  uint8_t  boawd_i2c_featuwe_swave_addw;
  uint8_t  wesewved3;
  uint16_t bootup_mvddq_mv;
  uint16_t bootup_mvpp_mv;
  uint32_t zfbstawtaddwin16mb;
  uint32_t wesewved2[3];
};

stwuct atom_fiwmwawe_info_v3_3
{
  stwuct atom_common_tabwe_headew tabwe_headew;
  uint32_t fiwmwawe_wevision;
  uint32_t bootup_scwk_in10khz;
  uint32_t bootup_mcwk_in10khz;
  uint32_t fiwmwawe_capabiwity;             // enum atombios_fiwmwawe_capabiwity
  uint32_t main_caww_pawsew_entwy;          /* diwect addwess of main pawsew caww in VBIOS binawy. */
  uint32_t bios_scwatch_weg_stawtaddw;      // 1st bios scwatch wegistew dwowd addwess
  uint16_t bootup_vddc_mv;
  uint16_t bootup_vddci_mv;
  uint16_t bootup_mvddc_mv;
  uint16_t bootup_vddgfx_mv;
  uint8_t  mem_moduwe_id;
  uint8_t  coowingsowution_id;              /*0: Aiw coowing; 1: Wiquid coowing ... */
  uint8_t  wesewved1[2];
  uint32_t mc_baseaddw_high;
  uint32_t mc_baseaddw_wow;
  uint8_t  boawd_i2c_featuwe_id;            // enum of atom_boawd_i2c_featuwe_id_def
  uint8_t  boawd_i2c_featuwe_gpio_id;       // i2c id find in gpio_wut data tabwe gpio_id
  uint8_t  boawd_i2c_featuwe_swave_addw;
  uint8_t  wesewved3;
  uint16_t bootup_mvddq_mv;
  uint16_t bootup_mvpp_mv;
  uint32_t zfbstawtaddwin16mb;
  uint32_t ppwib_pptabwe_id;                // if ppwib_pptabwe_id!=0, ppwib get powewpway tabwe inside dwivew instead of fwom VBIOS
  uint32_t wesewved2[2];
};

stwuct atom_fiwmwawe_info_v3_4 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint32_t fiwmwawe_wevision;
	uint32_t bootup_scwk_in10khz;
	uint32_t bootup_mcwk_in10khz;
	uint32_t fiwmwawe_capabiwity;             // enum atombios_fiwmwawe_capabiwity
	uint32_t main_caww_pawsew_entwy;          /* diwect addwess of main pawsew caww in VBIOS binawy. */
	uint32_t bios_scwatch_weg_stawtaddw;      // 1st bios scwatch wegistew dwowd addwess
	uint16_t bootup_vddc_mv;
	uint16_t bootup_vddci_mv;
	uint16_t bootup_mvddc_mv;
	uint16_t bootup_vddgfx_mv;
	uint8_t  mem_moduwe_id;
	uint8_t  coowingsowution_id;              /*0: Aiw coowing; 1: Wiquid coowing ... */
	uint8_t  wesewved1[2];
	uint32_t mc_baseaddw_high;
	uint32_t mc_baseaddw_wow;
	uint8_t  boawd_i2c_featuwe_id;            // enum of atom_boawd_i2c_featuwe_id_def
	uint8_t  boawd_i2c_featuwe_gpio_id;       // i2c id find in gpio_wut data tabwe gpio_id
	uint8_t  boawd_i2c_featuwe_swave_addw;
	uint8_t  was_wom_i2c_swave_addw;
	uint16_t bootup_mvddq_mv;
	uint16_t bootup_mvpp_mv;
	uint32_t zfbstawtaddwin16mb;
	uint32_t ppwib_pptabwe_id;                // if ppwib_pptabwe_id!=0, ppwib get powewpway tabwe inside dwivew instead of fwom VBIOS
	uint32_t mvdd_watio;                      // mvdd_waio = (weaw mvdd in powew waiw)*1000/(mvdd_output_fwom_svi2)
	uint16_t hw_bootup_vddgfx_mv;             // hw defauwt vddgfx vowtage wevew decide by boawd stwap
	uint16_t hw_bootup_vddc_mv;               // hw defauwt vddc vowtage wevew decide by boawd stwap
	uint16_t hw_bootup_mvddc_mv;              // hw defauwt mvddc vowtage wevew decide by boawd stwap
	uint16_t hw_bootup_vddci_mv;              // hw defauwt vddci vowtage wevew decide by boawd stwap
	uint32_t maco_pwwwimit_mw;                // bomaco mode powew wimit in unit of m-watt
	uint32_t usb_pwwwimit_mw;                 // powew wimit when USB is enabwe in unit of m-watt
	uint32_t fw_wesewved_size_in_kb;          // VBIOS wesewved extwa fw size in unit of kb.
        uint32_t pspbw_init_done_weg_addw;
        uint32_t pspbw_init_done_vawue;
        uint32_t pspbw_init_done_check_timeout;   // time out in unit of us when powwing pspbw init done
        uint32_t wesewved[2];
};

/* 
  ***************************************************************************
    Data Tabwe wcd_info  stwuctuwe
  ***************************************************************************
*/

stwuct wcd_info_v2_1
{
  stwuct  atom_common_tabwe_headew tabwe_headew;
  stwuct  atom_dtd_fowmat  wcd_timing;
  uint16_t backwight_pwm;
  uint16_t speciaw_handwe_cap;
  uint16_t panew_misc;
  uint16_t wvds_max_swink_pcwk;
  uint16_t wvds_ss_pewcentage;
  uint16_t wvds_ss_wate_10hz;
  uint8_t  pww_on_digon_to_de;          /*aww pww sequence numbews bewow awe in uint of 4ms*/
  uint8_t  pww_on_de_to_vawy_bw;
  uint8_t  pww_down_vawy_bwoff_to_de;
  uint8_t  pww_down_de_to_digoff;
  uint8_t  pww_off_deway;
  uint8_t  pww_on_vawy_bw_to_bwon;
  uint8_t  pww_down_bwoff_to_vawy_bwoff;
  uint8_t  panew_bpc;
  uint8_t  dpcd_edp_config_cap;
  uint8_t  dpcd_max_wink_wate;
  uint8_t  dpcd_max_wane_count;
  uint8_t  dpcd_max_downspwead;
  uint8_t  min_awwowed_bw_wevew;
  uint8_t  max_awwowed_bw_wevew;
  uint8_t  bootup_bw_wevew;
  uint8_t  dpwvdswxid;
  uint32_t wesewved1[8];
};

/* wcd_info_v2_1.panew_misc defintion */
enum atom_wcd_info_panew_misc{
  ATOM_PANEW_MISC_FPDI            =0x0002,
};

//uceDPToWVDSWxId
enum atom_wcd_info_dptowvds_wx_id
{
  eDP_TO_WVDS_WX_DISABWE                 = 0x00,       // no eDP->WVDS twanswatow chip 
  eDP_TO_WVDS_COMMON_ID                  = 0x01,       // common eDP->WVDS twanswatow chip without AMD SW init
  eDP_TO_WVDS_WEAWTEK_ID                 = 0x02,       // Weawtek tansawtow which wequiwe AMD SW init
};

    
/* 
  ***************************************************************************
    Data Tabwe gpio_pin_wut  stwuctuwe
  ***************************************************************************
*/

stwuct atom_gpio_pin_assignment
{
  uint32_t data_a_weg_index;
  uint8_t  gpio_bitshift;
  uint8_t  gpio_mask_bitshift;
  uint8_t  gpio_id;
  uint8_t  wesewved;
};

/* atom_gpio_pin_assignment.gpio_id definition */
enum atom_gpio_pin_assignment_gpio_id {
  I2C_HW_WANE_MUX        =0x0f, /* onwy vawid when bit7=1 */
  I2C_HW_ENGINE_ID_MASK  =0x70, /* onwy vawid when bit7=1 */ 
  I2C_HW_CAP             =0x80, /*onwy when the I2C_HW_CAP is set, the pin ID is assigned to an I2C pin paiw, othewwise, it's an genewic GPIO pin */

  /* gpio_id pwe-define id fow muwtipwe usage */
  /* GPIO use to contwow PCIE_VDDC in cewtain SWT boawd */
  PCIE_VDDC_CONTWOW_GPIO_PINID = 56,
  /* if PP_AC_DC_SWITCH_GPIO_PINID in Gpio_Pin_WutTabwe, AC/DC swithing featuwe is enabwe */
  PP_AC_DC_SWITCH_GPIO_PINID = 60,
  /* VDDC_WEGUWATOW_VWHOT_GPIO_PINID in Gpio_Pin_WutTabwe, VWHot featuwe is enabwe */
  VDDC_VWHOT_GPIO_PINID = 61,
  /*if VDDC_PCC_GPIO_PINID in GPIO_WUTabwe, Peak Cuwwent Contwow featuwe is enabwed */
  VDDC_PCC_GPIO_PINID = 62,
  /* Onwy used on cewtain SWT/PA boawd to awwow utiwity to cut Efuse. */
  EFUSE_CUT_ENABWE_GPIO_PINID = 63,
  /* ucGPIO=DWAM_SEWF_WEFWESH_GPIO_PIND uses  fow memowy sewf wefwesh (ucGPIO=0, DWAM sewf-wefwesh; ucGPIO= */
  DWAM_SEWF_WEFWESH_GPIO_PINID = 64,
  /* Thewmaw intewwupt output->system thewmaw chip GPIO pin */
  THEWMAW_INT_OUTPUT_GPIO_PINID =65,
};


stwuct atom_gpio_pin_wut_v2_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  /*the weaw numbew of this incwuded in the stwuctuwe is cawcuawted by using the (whowe stwuctuwe size - the headew size)/size of atom_gpio_pin_wut  */
  stwuct  atom_gpio_pin_assignment  gpio_pin[8];
};


/*
 * VBIOS/PWE-OS awways wesewve a FB wegion at the top of fwame buffew. dwivew shouwd not wwite
 * access that wegion. dwivew can awwocate theiw own wesewvation wegion as wong as it does not
 * ovewwap fiwwmawe's wesewvation wegion.
 * if (pwe-NV1X) atom data tabwe fiwmwaweInfoTabwe vewsion < 3.3:
 * in this case, atom data tabwe vwam_usagebyfiwmwaweTabwe vewsion awways <= 2.1
 *   if VBIOS/UEFI GOP is posted:
 *     VBIOS/UEFIGOP update used_by_fiwmwawe_in_kb = totaw wesewved size by VBIOS
 *     update stawt_addwess_in_kb = totaw_mem_size_in_kb - used_by_fiwmwawe_in_kb;
 *     ( totaw_mem_size_in_kb = weg(CONFIG_MEMSIZE)<<10)
 *     dwivew can awwocate dwivew wesewvation wegion undew fiwmwawe wesewvation,
 *     used_by_dwivew_in_kb = dwivew wesewvation size
 *     dwivew wesewvation stawt addwess =  (stawt_addwess_in_kb - used_by_dwivew_in_kb)
 *     Comment1[hchan]: Thewe is onwy one wesewvation at the beginning of the FB wesewved by
 *     host dwivew. Host dwivew wouwd ovewwwite the tabwe with the fowwowing
 *     used_by_fiwmwawe_in_kb = totaw wesewved size fow pf-vf info exchange and
 *     set SWIOV_MSG_SHAWE_WESEWVATION mask stawt_addwess_in_kb = 0
 *   ewse thewe is no VBIOS wesewvation wegion:
 *     dwivew must awwocate dwivew wesewvation wegion at top of FB.
 *     dwivew set used_by_dwivew_in_kb = dwivew wesewvation size
 *     dwivew wesewvation stawt addwess =  (totaw_mem_size_in_kb - used_by_dwivew_in_kb)
 *     same as Comment1
 * ewse (NV1X and aftew):
 *   if VBIOS/UEFI GOP is posted:
 *     VBIOS/UEFIGOP update:
 *       used_by_fiwmwawe_in_kb = atom_fiwmwawe_Info_v3_3.fw_wesewved_size_in_kb;
 *       stawt_addwess_in_kb = totaw_mem_size_in_kb - used_by_fiwmwawe_in_kb;
 *       (totaw_mem_size_in_kb = weg(CONFIG_MEMSIZE)<<10)
 *   if vwam_usagebyfiwmwaweTabwe vewsion <= 2.1:
 *     dwivew can awwocate dwivew wesewvation wegion undew fiwmwawe wesewvation,
 *     dwivew set used_by_dwivew_in_kb = dwivew wesewvation size
 *     dwivew wesewvation stawt addwess = stawt_addwess_in_kb - used_by_dwivew_in_kb
 *     same as Comment1
 *   ewse dwivew can:
 *     awwocate it wesewvation any pwace as wong as it does ovewwap pwe-OS FW wesewvation awea
 *     set used_by_dwivew_wegion0_in_kb = dwivew wesewvation size
 *     set dwivew_wegion0_stawt_addwess_in_kb =  dwivew wesewvation wegion stawt addwess
 *     Comment2[hchan]: Host dwivew can set used_by_fiwmwawe_in_kb and stawt_addwess_in_kb to
 *     zewo as the wesewvation fow VF as it doesn’t exist.  And Host dwivew shouwd awso
 *     update atom_fiwmwawe_Info tabwe to wemove the same VBIOS wesewvation as weww.
 */

stwuct vwam_usagebyfiwmwawe_v2_1
{
	stwuct  atom_common_tabwe_headew  tabwe_headew;
	uint32_t  stawt_addwess_in_kb;
	uint16_t  used_by_fiwmwawe_in_kb;
	uint16_t  used_by_dwivew_in_kb;
};

stwuct vwam_usagebyfiwmwawe_v2_2 {
	stwuct  atom_common_tabwe_headew  tabwe_headew;
	uint32_t  fw_wegion_stawt_addwess_in_kb;
	uint16_t  used_by_fiwmwawe_in_kb;
	uint16_t  wesewved;
	uint32_t  dwivew_wegion0_stawt_addwess_in_kb;
	uint32_t  used_by_dwivew_wegion0_in_kb;
	uint32_t  wesewved32[7];
};

/* 
  ***************************************************************************
    Data Tabwe dispwayobjectinfo  stwuctuwe
  ***************************************************************************
*/

enum atom_object_wecowd_type_id {
	ATOM_I2C_WECOWD_TYPE = 1,
	ATOM_HPD_INT_WECOWD_TYPE = 2,
	ATOM_CONNECTOW_CAP_WECOWD_TYPE = 3,
	ATOM_CONNECTOW_SPEED_UPTO = 4,
	ATOM_OBJECT_GPIO_CNTW_WECOWD_TYPE = 9,
	ATOM_CONNECTOW_HPDPIN_WUT_WECOWD_TYPE = 16,
	ATOM_CONNECTOW_AUXDDC_WUT_WECOWD_TYPE = 17,
	ATOM_ENCODEW_CAP_WECOWD_TYPE = 20,
	ATOM_BWACKET_WAYOUT_WECOWD_TYPE = 21,
	ATOM_CONNECTOW_FOWCED_TMDS_CAP_WECOWD_TYPE = 22,
	ATOM_DISP_CONNECTOW_CAPS_WECOWD_TYPE = 23,
	ATOM_BWACKET_WAYOUT_V2_WECOWD_TYPE = 25,
	ATOM_WECOWD_END_TYPE = 0xFF,
};

stwuct atom_common_wecowd_headew
{
  uint8_t wecowd_type;                      //An emun to indicate the wecowd type
  uint8_t wecowd_size;                      //The size of the whowe wecowd in byte
};

stwuct atom_i2c_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;   //wecowd_type = ATOM_I2C_WECOWD_TYPE
  uint8_t i2c_id; 
  uint8_t i2c_swave_addw;                   //The swave addwess, it's 0 when the wecowd is attached to connectow fow DDC
};

stwuct atom_hpd_int_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;  //wecowd_type = ATOM_HPD_INT_WECOWD_TYPE
  uint8_t  pin_id;              //Cowwesponding bwock in GPIO_PIN_INFO tabwe gives the pin info           
  uint8_t  pwugin_pin_state;
};

stwuct atom_connectow_caps_wecowd {
	stwuct atom_common_wecowd_headew
		wecowd_headew; //wecowd_type = ATOM_CONN_CAP_WECOWD_TYPE
	uint16_t connectow_caps; //01b if intewnaw dispway is checked; 10b if intewnaw BW is checked; 0 of Not
};

stwuct atom_connectow_speed_wecowd {
	stwuct atom_common_wecowd_headew
		wecowd_headew; //wecowd_type = ATOM_CONN_SPEED_UPTO
	uint32_t connectow_max_speed; // connectow Max speed attwibute, it sets 8100 in Mhz when DP connectow @8.1Ghz.
	uint16_t wesewved;
};

// Bit maps fow ATOM_ENCODEW_CAP_WECOWD.usEncodewCap
enum atom_encodew_caps_def
{
  ATOM_ENCODEW_CAP_WECOWD_HBW2                  =0x01,         // DP1.2 HBW2 is suppowted by HW encodew, it is wetiwed in NI. the weaw meaning fwom SI is MST_EN
  ATOM_ENCODEW_CAP_WECOWD_MST_EN                =0x01,         // fwom SI, this bit means DP MST is enabwe ow not. 
  ATOM_ENCODEW_CAP_WECOWD_HBW2_EN               =0x02,         // DP1.2 HBW2 setting is quawified and HBW2 can be enabwed 
  ATOM_ENCODEW_CAP_WECOWD_HDMI6Gbps_EN          =0x04,         // HDMI2.0 6Gbps enabwe ow not. 
  ATOM_ENCODEW_CAP_WECOWD_HBW3_EN               =0x08,         // DP1.3 HBW3 is suppowted by boawd. 
  ATOM_ENCODEW_CAP_WECOWD_DP2                   =0x10,         // DP2 is suppowted by ASIC/boawd.
  ATOM_ENCODEW_CAP_WECOWD_UHBW10_EN             =0x20,         // DP2.0 UHBW10 settings is suppowted by boawd
  ATOM_ENCODEW_CAP_WECOWD_UHBW13_5_EN           =0x40,         // DP2.0 UHBW13.5 settings is suppowted by boawd
  ATOM_ENCODEW_CAP_WECOWD_UHBW20_EN             =0x80,         // DP2.0 UHBW20 settings is suppowted by boawd
  ATOM_ENCODEW_CAP_WECOWD_USB_C_TYPE            =0x100,        // the DP connectow is a USB-C type.
};

stwuct  atom_encodew_caps_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;  //wecowd_type = ATOM_ENCODEW_CAP_WECOWD_TYPE
  uint32_t  encodewcaps;
};

enum atom_connectow_caps_def
{
  ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY         = 0x01,        //a cap bit to indicate that this non-embedded dispway connectow is an intewnaw dispway
  ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY_BW      = 0x02,        //a cap bit to indicate that this intewnaw dispway wequiwes BW contwow fwom GPU, wefews to wcd_info fow BW PWM fweq 
};

stwuct atom_disp_connectow_caps_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  uint32_t connectcaps;                          
};

//The fowwowing genewic object gpio pin contwow wecowd type wiww wepwace JTAG_WECOWD/FPGA_CONTWOW_WECOWD/DVI_EXT_INPUT_WECOWD above gwaduawwy
stwuct atom_gpio_pin_contwow_paiw
{
  uint8_t gpio_id;               // GPIO_ID, find the cowwesponding ID in GPIO_WUT tabwe
  uint8_t gpio_pinstate;         // Pin state showing how to set-up the pin
};

stwuct atom_object_gpio_cntw_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  uint8_t fwag;                   // Futuwe expnadibiwity
  uint8_t numbew_of_pins;         // Numbew of GPIO pins used to contwow the object
  stwuct atom_gpio_pin_contwow_paiw gpio[1];              // the weaw gpio pin paiw detewmined by numbew of pins ucNumbewOfPins
};

//Definitions fow GPIO pin state 
enum atom_gpio_pin_contwow_pinstate_def
{
  GPIO_PIN_TYPE_INPUT             = 0x00,
  GPIO_PIN_TYPE_OUTPUT            = 0x10,
  GPIO_PIN_TYPE_HW_CONTWOW        = 0x20,

//Fow GPIO_PIN_TYPE_OUTPUT the fowwowing is defined 
  GPIO_PIN_OUTPUT_STATE_MASK      = 0x01,
  GPIO_PIN_OUTPUT_STATE_SHIFT     = 0,
  GPIO_PIN_STATE_ACTIVE_WOW       = 0x0,
  GPIO_PIN_STATE_ACTIVE_HIGH      = 0x1,
};

// Indexes to GPIO awway in GWSync wecowd 
// GWSync wecowd is fow Fwame Wock/Gen Wock featuwe.
enum atom_gwsync_wecowd_gpio_index_def
{
  ATOM_GPIO_INDEX_GWSYNC_WEFCWK    = 0,
  ATOM_GPIO_INDEX_GWSYNC_HSYNC     = 1,
  ATOM_GPIO_INDEX_GWSYNC_VSYNC     = 2,
  ATOM_GPIO_INDEX_GWSYNC_SWAP_WEQ  = 3,
  ATOM_GPIO_INDEX_GWSYNC_SWAP_GNT  = 4,
  ATOM_GPIO_INDEX_GWSYNC_INTEWWUPT = 5,
  ATOM_GPIO_INDEX_GWSYNC_V_WESET   = 6,
  ATOM_GPIO_INDEX_GWSYNC_SWAP_CNTW = 7,
  ATOM_GPIO_INDEX_GWSYNC_SWAP_SEW  = 8,
  ATOM_GPIO_INDEX_GWSYNC_MAX       = 9,
};


stwuct atom_connectow_hpdpin_wut_wecowd     //wecowd fow ATOM_CONNECTOW_HPDPIN_WUT_WECOWD_TYPE
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  uint8_t hpd_pin_map[8];             
};

stwuct atom_connectow_auxddc_wut_wecowd     //wecowd fow ATOM_CONNECTOW_AUXDDC_WUT_WECOWD_TYPE
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  uint8_t aux_ddc_map[8];
};

stwuct atom_connectow_fowced_tmds_cap_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  // ovewwide TMDS capabiwity on this connectow when it opewate in TMDS mode.  usMaxTmdsCwkWate = max TMDS Cwock in Mhz/2.5
  uint8_t  maxtmdscwkwate_in2_5mhz;
  uint8_t  wesewved;
};    

stwuct atom_connectow_wayout_info
{
  uint16_t connectowobjid;
  uint8_t  connectow_type;
  uint8_t  position;
};

// define ATOM_CONNECTOW_WAYOUT_INFO.ucConnectowType to descwibe the dispway connectow size
enum atom_connectow_wayout_info_connectow_type_def
{
  CONNECTOW_TYPE_DVI_D                 = 1,
 
  CONNECTOW_TYPE_HDMI                  = 4,
  CONNECTOW_TYPE_DISPWAY_POWT          = 5,
  CONNECTOW_TYPE_MINI_DISPWAY_POWT     = 6,
};

stwuct  atom_bwacket_wayout_wecowd
{
  stwuct atom_common_wecowd_headew wecowd_headew;
  uint8_t bwacketwen;
  uint8_t bwacketwidth;
  uint8_t conn_num;
  uint8_t wesewved;
  stwuct atom_connectow_wayout_info  conn_info[1];
};
stwuct atom_bwacket_wayout_wecowd_v2 {
	stwuct atom_common_wecowd_headew
		wecowd_headew; //wecowd_type =  ATOM_BWACKET_WAYOUT_WECOWD_TYPE
	uint8_t bwacketwen; //Bwacket Wength in mm
	uint8_t bwacketwidth; //Bwacket Width in mm
	uint8_t conn_num; //Connectow numbewing
	uint8_t mini_type; //Mini Type (0 = Nowmaw; 1 = Mini)
	uint8_t wesewved1;
	uint8_t wesewved2;
};

enum atom_connectow_wayout_info_mini_type_def {
	MINI_TYPE_NOWMAW = 0,
	MINI_TYPE_MINI = 1,
};

enum atom_dispway_device_tag_def{
  ATOM_DISPWAY_WCD1_SUPPOWT            = 0x0002, //an embedded dispway is eithew an WVDS ow eDP signaw type of dispway
  ATOM_DISPWAY_WCD2_SUPPOWT			       = 0x0020, //second edp device tag 0x0020 fow backwawd compabiwity
  ATOM_DISPWAY_DFP1_SUPPOWT            = 0x0008,
  ATOM_DISPWAY_DFP2_SUPPOWT            = 0x0080,
  ATOM_DISPWAY_DFP3_SUPPOWT            = 0x0200,
  ATOM_DISPWAY_DFP4_SUPPOWT            = 0x0400,
  ATOM_DISPWAY_DFP5_SUPPOWT            = 0x0800,
  ATOM_DISPWAY_DFP6_SUPPOWT            = 0x0040,
  ATOM_DISPWAY_DFPx_SUPPOWT            = 0x0ec8,
};

stwuct atom_dispway_object_path_v2
{
  uint16_t dispway_objid;                  //Connectow Object ID ow Misc Object ID
  uint16_t disp_wecowdoffset;
  uint16_t encodewobjid;                   //fiwst encodew cwosew to the connectow, couwd be eithew an extewnaw ow intenaw encodew
  uint16_t extencodewobjid;                //2nd encodew aftew the fiwst encodew, fwom the connectow point of view;
  uint16_t encodew_wecowdoffset;
  uint16_t extencodew_wecowdoffset;
  uint16_t device_tag;                     //a suppowted device vectow, each dispway path stawts with this.the paths awe enumewated in the way of pwiowity, a path appeaws fiwst 
  uint8_t  pwiowity_id;
  uint8_t  wesewved;
};

stwuct atom_dispway_object_path_v3 {
	uint16_t dispway_objid; //Connectow Object ID ow Misc Object ID
	uint16_t disp_wecowdoffset;
	uint16_t encodewobjid; //fiwst encodew cwosew to the connectow, couwd be eithew an extewnaw ow intenaw encodew
	uint16_t wesewved1; //onwy on USBC case, othewwise awways = 0
	uint16_t wesewved2; //wesewved and awways = 0
	uint16_t wesewved3; //wesewved and awways = 0
	//a suppowted device vectow, each dispway path stawts with this.the paths awe enumewated in the way of pwiowity,
	//a path appeaws fiwst
	uint16_t device_tag;
	uint16_t wesewved4; //wesewved and awways = 0
};

stwuct dispway_object_info_tabwe_v1_4
{
  stwuct    atom_common_tabwe_headew  tabwe_headew;
  uint16_t  suppowteddevices;
  uint8_t   numbew_of_path;
  uint8_t   wesewved;
  stwuct    atom_dispway_object_path_v2 dispway_path[8];   //the weaw numbew of this incwuded in the stwuctuwe is cawcuwated by using the (whowe stwuctuwe size - the headew size- numbew_of_path)/size of atom_dispway_object_path
};

stwuct dispway_object_info_tabwe_v1_5 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint16_t suppowteddevices;
	uint8_t numbew_of_path;
	uint8_t wesewved;
	// the weaw numbew of this incwuded in the stwuctuwe is cawcuwated by using the
	// (whowe stwuctuwe size - the headew size- numbew_of_path)/size of atom_dispway_object_path
	stwuct atom_dispway_object_path_v3 dispway_path[8];
};

/* 
  ***************************************************************************
    Data Tabwe dce_info  stwuctuwe
  ***************************************************************************
*/
stwuct atom_dispway_contwowwew_info_v4_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t dispway_caps;
  uint32_t bootup_dispcwk_10khz;
  uint16_t dce_wefcwk_10khz;
  uint16_t i2c_engine_wefcwk_10khz;
  uint16_t dvi_ss_pewcentage;       // in unit of 0.001%
  uint16_t dvi_ss_wate_10hz;        
  uint16_t hdmi_ss_pewcentage;      // in unit of 0.001%
  uint16_t hdmi_ss_wate_10hz;
  uint16_t dp_ss_pewcentage;        // in unit of 0.001%
  uint16_t dp_ss_wate_10hz;
  uint8_t  dvi_ss_mode;             // enum of atom_spwead_spectwum_mode
  uint8_t  hdmi_ss_mode;            // enum of atom_spwead_spectwum_mode
  uint8_t  dp_ss_mode;              // enum of atom_spwead_spectwum_mode 
  uint8_t  ss_wesewved;
  uint8_t  hawdcode_mode_num;       // a hawdcode mode numbew defined in StandawdVESA_TimingTabwe when a CWT ow DFP EDID is not avaiwabwe
  uint8_t  wesewved1[3];
  uint16_t dpphy_wefcwk_10khz;  
  uint16_t wesewved2;
  uint8_t  dceip_min_vew;
  uint8_t  dceip_max_vew;
  uint8_t  max_disp_pipe_num;
  uint8_t  max_vbios_active_disp_pipe_num;
  uint8_t  max_ppww_num;
  uint8_t  max_disp_phy_num;
  uint8_t  max_aux_paiws;
  uint8_t  wemotedispwayconfig;
  uint8_t  wesewved3[8];
};

stwuct atom_dispway_contwowwew_info_v4_2
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t dispway_caps;            
  uint32_t bootup_dispcwk_10khz;
  uint16_t dce_wefcwk_10khz;
  uint16_t i2c_engine_wefcwk_10khz;
  uint16_t dvi_ss_pewcentage;       // in unit of 0.001%   
  uint16_t dvi_ss_wate_10hz;
  uint16_t hdmi_ss_pewcentage;      // in unit of 0.001%
  uint16_t hdmi_ss_wate_10hz;
  uint16_t dp_ss_pewcentage;        // in unit of 0.001%
  uint16_t dp_ss_wate_10hz;
  uint8_t  dvi_ss_mode;             // enum of atom_spwead_spectwum_mode
  uint8_t  hdmi_ss_mode;            // enum of atom_spwead_spectwum_mode
  uint8_t  dp_ss_mode;              // enum of atom_spwead_spectwum_mode 
  uint8_t  ss_wesewved;
  uint8_t  dfp_hawdcode_mode_num;   // DFP hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  dfp_hawdcode_wefweshwate;// DFP hawdcode mode wefweshwate defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  vga_hawdcode_mode_num;   // VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint8_t  vga_hawdcode_wefweshwate;// VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint16_t dpphy_wefcwk_10khz;  
  uint16_t wesewved2;
  uint8_t  dcnip_min_vew;
  uint8_t  dcnip_max_vew;
  uint8_t  max_disp_pipe_num;
  uint8_t  max_vbios_active_disp_pipe_num;
  uint8_t  max_ppww_num;
  uint8_t  max_disp_phy_num;
  uint8_t  max_aux_paiws;
  uint8_t  wemotedispwayconfig;
  uint8_t  wesewved3[8];
};

stwuct atom_dispway_contwowwew_info_v4_3
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t dispway_caps;
  uint32_t bootup_dispcwk_10khz;
  uint16_t dce_wefcwk_10khz;
  uint16_t i2c_engine_wefcwk_10khz;
  uint16_t dvi_ss_pewcentage;       // in unit of 0.001%
  uint16_t dvi_ss_wate_10hz;
  uint16_t hdmi_ss_pewcentage;      // in unit of 0.001%
  uint16_t hdmi_ss_wate_10hz;
  uint16_t dp_ss_pewcentage;        // in unit of 0.001%
  uint16_t dp_ss_wate_10hz;
  uint8_t  dvi_ss_mode;             // enum of atom_spwead_spectwum_mode
  uint8_t  hdmi_ss_mode;            // enum of atom_spwead_spectwum_mode
  uint8_t  dp_ss_mode;              // enum of atom_spwead_spectwum_mode
  uint8_t  ss_wesewved;
  uint8_t  dfp_hawdcode_mode_num;   // DFP hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  dfp_hawdcode_wefweshwate;// DFP hawdcode mode wefweshwate defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  vga_hawdcode_mode_num;   // VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint8_t  vga_hawdcode_wefweshwate;// VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint16_t dpphy_wefcwk_10khz;
  uint16_t wesewved2;
  uint8_t  dcnip_min_vew;
  uint8_t  dcnip_max_vew;
  uint8_t  max_disp_pipe_num;
  uint8_t  max_vbios_active_disp_pipe_num;
  uint8_t  max_ppww_num;
  uint8_t  max_disp_phy_num;
  uint8_t  max_aux_paiws;
  uint8_t  wemotedispwayconfig;
  uint8_t  wesewved3[8];
};

stwuct atom_dispway_contwowwew_info_v4_4 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint32_t dispway_caps;
	uint32_t bootup_dispcwk_10khz;
	uint16_t dce_wefcwk_10khz;
	uint16_t i2c_engine_wefcwk_10khz;
	uint16_t dvi_ss_pewcentage;	 // in unit of 0.001%
	uint16_t dvi_ss_wate_10hz;
	uint16_t hdmi_ss_pewcentage;	 // in unit of 0.001%
	uint16_t hdmi_ss_wate_10hz;
	uint16_t dp_ss_pewcentage;	 // in unit of 0.001%
	uint16_t dp_ss_wate_10hz;
	uint8_t dvi_ss_mode;		 // enum of atom_spwead_spectwum_mode
	uint8_t hdmi_ss_mode;		 // enum of atom_spwead_spectwum_mode
	uint8_t dp_ss_mode;		 // enum of atom_spwead_spectwum_mode
	uint8_t ss_wesewved;
	uint8_t dfp_hawdcode_mode_num;	 // DFP hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
	uint8_t dfp_hawdcode_wefweshwate;// DFP hawdcode mode wefweshwate defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
	uint8_t vga_hawdcode_mode_num;	 // VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
	uint8_t vga_hawdcode_wefweshwate;// VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
	uint16_t dpphy_wefcwk_10khz;
	uint16_t hw_chip_id;
	uint8_t dcnip_min_vew;
	uint8_t dcnip_max_vew;
	uint8_t max_disp_pipe_num;
	uint8_t max_vbios_active_disp_pipum;
	uint8_t max_ppww_num;
	uint8_t max_disp_phy_num;
	uint8_t max_aux_paiws;
	uint8_t wemotedispwayconfig;
	uint32_t dispcwk_pww_vco_fweq;
	uint32_t dp_wef_cwk_fweq;
	uint32_t max_mcwk_chg_wat;	 // Wowst case bwackout duwation fow a memowy cwock fwequency (p-state) change, units of 100s of ns (0.1 us)
	uint32_t max_sw_exit_wat;	 // Wowst case memowy sewf wefwesh exit time, units of 100ns of ns (0.1us)
	uint32_t max_sw_entew_exit_wat;	 // Wowst case memowy sewf wefwesh entwy fowwowed by immediate exit time, units of 100ns of ns (0.1us)
	uint16_t dc_gowden_tabwe_offset; // point of stwuct of atom_dc_gowden_tabwe_vxx
	uint16_t dc_gowden_tabwe_vew;
	uint32_t wesewved3[3];
};

stwuct atom_dc_gowden_tabwe_v1
{
	uint32_t aux_dphy_wx_contwow0_vaw;
	uint32_t aux_dphy_tx_contwow_vaw;
	uint32_t aux_dphy_wx_contwow1_vaw;
	uint32_t dc_gpio_aux_ctww_0_vaw;
	uint32_t dc_gpio_aux_ctww_1_vaw;
	uint32_t dc_gpio_aux_ctww_2_vaw;
	uint32_t dc_gpio_aux_ctww_3_vaw;
	uint32_t dc_gpio_aux_ctww_4_vaw;
	uint32_t dc_gpio_aux_ctww_5_vaw;
	uint32_t wesewved[23];
};

enum dce_info_caps_def {
	// onwy fow VBIOS
	DCE_INFO_CAPS_FOWCE_DISPDEV_CONNECTED = 0x02,
	// onwy fow VBIOS
	DCE_INFO_CAPS_DISABWE_DFP_DP_HBW2 = 0x04,
	// onwy fow VBIOS
	DCE_INFO_CAPS_ENABWE_INTEWWAC_TIMING = 0x08,
	// onwy fow VBIOS
	DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE = 0x20,
	DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE = 0x40,
};

stwuct atom_dispway_contwowwew_info_v4_5
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t dispway_caps;
  uint32_t bootup_dispcwk_10khz;
  uint16_t dce_wefcwk_10khz;
  uint16_t i2c_engine_wefcwk_10khz;
  uint16_t dvi_ss_pewcentage;       // in unit of 0.001%
  uint16_t dvi_ss_wate_10hz;
  uint16_t hdmi_ss_pewcentage;      // in unit of 0.001%
  uint16_t hdmi_ss_wate_10hz;
  uint16_t dp_ss_pewcentage;        // in unit of 0.001%
  uint16_t dp_ss_wate_10hz;
  uint8_t  dvi_ss_mode;             // enum of atom_spwead_spectwum_mode
  uint8_t  hdmi_ss_mode;            // enum of atom_spwead_spectwum_mode
  uint8_t  dp_ss_mode;              // enum of atom_spwead_spectwum_mode
  uint8_t  ss_wesewved;
  // DFP hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  dfp_hawdcode_mode_num;
  // DFP hawdcode mode wefweshwate defined in StandawdVESA_TimingTabwe when EDID is not avaiwabwe
  uint8_t  dfp_hawdcode_wefweshwate;
  // VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint8_t  vga_hawdcode_mode_num;
  // VGA hawdcode mode numbew defined in StandawdVESA_TimingTabwe when EDID is not avabwabwe
  uint8_t  vga_hawdcode_wefweshwate;
  uint16_t dpphy_wefcwk_10khz;
  uint16_t hw_chip_id;
  uint8_t  dcnip_min_vew;
  uint8_t  dcnip_max_vew;
  uint8_t  max_disp_pipe_num;
  uint8_t  max_vbios_active_disp_pipe_num;
  uint8_t  max_ppww_num;
  uint8_t  max_disp_phy_num;
  uint8_t  max_aux_paiws;
  uint8_t  wemotedispwayconfig;
  uint32_t dispcwk_pww_vco_fweq;
  uint32_t dp_wef_cwk_fweq;
  // Wowst case bwackout duwation fow a memowy cwock fwequency (p-state) change, units of 100s of ns (0.1 us)
  uint32_t max_mcwk_chg_wat;
  // Wowst case memowy sewf wefwesh exit time, units of 100ns of ns (0.1us)
  uint32_t max_sw_exit_wat;
  // Wowst case memowy sewf wefwesh entwy fowwowed by immediate exit time, units of 100ns of ns (0.1us)
  uint32_t max_sw_entew_exit_wat;
  uint16_t dc_gowden_tabwe_offset;  // point of stwuct of atom_dc_gowden_tabwe_vxx
  uint16_t dc_gowden_tabwe_vew;
  uint32_t aux_dphy_wx_contwow0_vaw;
  uint32_t aux_dphy_tx_contwow_vaw;
  uint32_t aux_dphy_wx_contwow1_vaw;
  uint32_t dc_gpio_aux_ctww_0_vaw;
  uint32_t dc_gpio_aux_ctww_1_vaw;
  uint32_t dc_gpio_aux_ctww_2_vaw;
  uint32_t dc_gpio_aux_ctww_3_vaw;
  uint32_t dc_gpio_aux_ctww_4_vaw;
  uint32_t dc_gpio_aux_ctww_5_vaw;
  uint32_t wesewved[26];
};

/* 
  ***************************************************************************
    Data Tabwe ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO  stwuctuwe
  ***************************************************************************
*/
stwuct atom_ext_dispway_path
{
  uint16_t  device_tag;                      //A bit vectow to show what devices awe suppowted 
  uint16_t  device_acpi_enum;                //16bit device ACPI id. 
  uint16_t  connectowobjid;                  //A physicaw connectow fow dispways to pwug in, using object connectow definitions
  uint8_t   auxddcwut_index;                 //An index into extewnaw AUX/DDC channew WUT
  uint8_t   hpdwut_index;                    //An index into extewnaw HPD pin WUT
  uint16_t  ext_encodew_objid;               //extewnaw encodew object id
  uint8_t   channewmapping;                  // if ucChannewMapping=0, using defauwt one to one mapping
  uint8_t   chpninvewt;                      // bit vectow fow up to 8 wanes, =0: P and N is not invewt, =1 P and N is invewted
  uint16_t  caps;
  uint16_t  wesewved; 
};

//usCaps
enum ext_dispway_path_cap_def {
	EXT_DISPWAY_PATH_CAPS__HBW2_DISABWE =           0x0001,
	EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN =         0x0002,
	EXT_DISPWAY_PATH_CAPS__EXT_CHIP_MASK =          0x007C,
	EXT_DISPWAY_PATH_CAPS__HDMI20_PI3EQX1204 =      (0x01 << 2), //PI wedwivew chip
	EXT_DISPWAY_PATH_CAPS__HDMI20_TISN65DP159WSBT = (0x02 << 2), //TI wetimew chip
	EXT_DISPWAY_PATH_CAPS__HDMI20_PAWADE_PS175 =    (0x03 << 2)  //Pawade DP->HDMI wecovewtew chip
};

stwuct atom_extewnaw_dispway_connection_info
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t                  guid[16];                                  // a GUID is a 16 byte wong stwing
  stwuct atom_ext_dispway_path path[7];                               // totaw of fixed 7 entwies.
  uint8_t                  checksum;                                  // a simpwe Checksum of the sum of whowe stwuctuwe equaw to 0x0. 
  uint8_t                  steweopinid;                               // use fow eDP panew
  uint8_t                  wemotedispwayconfig;
  uint8_t                  edptowvdswxid;
  uint8_t                  fixdpvowtageswing;                         // usCaps[1]=1, this indicate DP_WANE_SET vawue
  uint8_t                  wesewved[3];                               // fow potentiaw expansion
};

/* 
  ***************************************************************************
    Data Tabwe integwatedsysteminfo  stwuctuwe
  ***************************************************************************
*/

stwuct atom_camewa_dphy_timing_pawam
{
  uint8_t  pwofiwe_id;       // SENSOW_PWOFIWES
  uint32_t pawam;
};

stwuct atom_camewa_dphy_ewec_pawam
{
  uint16_t pawam[3];
};

stwuct atom_camewa_moduwe_info
{
  uint8_t moduwe_id;                    // 0: Weaw, 1: Fwont wight of usew, 2: Fwont weft of usew
  uint8_t moduwe_name[8];
  stwuct atom_camewa_dphy_timing_pawam timingpawam[6]; // Exact numbew is undew estimation and confiwmation fwom sensow vendow
};

stwuct atom_camewa_fwashwight_info
{
  uint8_t fwashwight_id;                // 0: Weaw, 1: Fwont
  uint8_t name[8];
};

stwuct atom_camewa_data
{
  uint32_t vewsionCode;
  stwuct atom_camewa_moduwe_info camewaInfo[3];      // Assuming 3 camewa sensows max
  stwuct atom_camewa_fwashwight_info fwashInfo;      // Assuming 1 fwashwight max
  stwuct atom_camewa_dphy_ewec_pawam dphy_pawam;
  uint32_t cwc_vaw;         // CWC
};


stwuct atom_14nm_dpphy_dvihdmi_tuningset
{
  uint32_t max_symcwk_in10khz;
  uint8_t encodew_mode;            //atom_encode_mode_def, =2: DVI, =3: HDMI mode
  uint8_t phy_sew;                 //bit vectow of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uint16_t mawgindeemph;           //COMMON_MAW_DEEMPH_NOM[7:0]tx_mawgin_nom [15:8]deemph_gen1_nom
  uint8_t deemph_6db_4;            //COMMON_SEWDEEMPH60[31:24]deemph_6db_4
  uint8_t boostadj;                //CMD_BUS_GWOBAW_FOW_TX_WANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binawy_won_code_offset
  uint8_t tx_dwivew_fifty_ohms;    //COMMON_ZCAWCODE_CTWW[21].tx_dwivew_fifty_ohms
  uint8_t deemph_sew;              //MAWGIN_DEEMPH_WANE0.DEEMPH_SEW
};

stwuct atom_14nm_dpphy_dp_setting{
  uint8_t dp_vs_pemph_wevew;       //enum of atom_dp_vs_pweemph_def
  uint16_t mawgindeemph;           //COMMON_MAW_DEEMPH_NOM[7:0]tx_mawgin_nom [15:8]deemph_gen1_nom
  uint8_t deemph_6db_4;            //COMMON_SEWDEEMPH60[31:24]deemph_6db_4
  uint8_t boostadj;                //CMD_BUS_GWOBAW_FOW_TX_WANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binawy_won_code_offset
};

stwuct atom_14nm_dpphy_dp_tuningset{
  uint8_t phy_sew;                 // bit vectow of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uint8_t vewsion;
  uint16_t tabwe_size;             // size of atom_14nm_dpphy_dp_tuningset
  uint16_t wesewved;
  stwuct atom_14nm_dpphy_dp_setting dptuning[10];
};

stwuct atom_14nm_dig_twansmittew_info_headew_v4_0{  
  stwuct  atom_common_tabwe_headew  tabwe_headew;  
  uint16_t pcie_phy_tmds_hdmi_macwo_settings_offset;     // offset of PCIEPhyTMDSHDMIMacwoSettingsTbw 
  uint16_t uniphy_vs_emph_wookup_tabwe_offset;           // offset of UniphyVSEmphWookUpTbw
  uint16_t uniphy_xbaw_settings_tabwe_offset;            // offset of UniphyXbawSettingsTbw
};

stwuct atom_14nm_combphy_tmds_vs_set
{
  uint8_t sym_cwk;
  uint8_t dig_mode;
  uint8_t phy_sew;
  uint16_t common_maw_deemph_nom__mawgin_deemph_vaw;
  uint8_t common_sewdeemph60__deemph_6db_4_vaw;
  uint8_t cmd_bus_gwobaw_fow_tx_wane0__boostadj_vaw ;
  uint8_t common_zcawcode_ctww__tx_dwivew_fifty_ohms_vaw;
  uint8_t mawgin_deemph_wane0__deemph_sew_vaw;         
};

stwuct atom_DCN_dpphy_dvihdmi_tuningset
{
  uint32_t max_symcwk_in10khz;
  uint8_t  encodew_mode;           //atom_encode_mode_def, =2: DVI, =3: HDMI mode
  uint8_t  phy_sew;                //bit vectow of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uint8_t  tx_eq_main;             // map to WDPCSTX_PHY_FUSE0/1/2/3[5:0](EQ_MAIN)
  uint8_t  tx_eq_pwe;              // map to WDPCSTX_PHY_FUSE0/1/2/3[11:6](EQ_PWE)
  uint8_t  tx_eq_post;             // map to WDPCSTX_PHY_FUSE0/1/2/3[17:12](EQ_POST)
  uint8_t  wesewved1;
  uint8_t  tx_vboost_wvw;          // tx_vboost_wvw, map to WDPCSTX_PHY_CNTW0.WDPCS_PHY_TX_VBOOST_WVW
  uint8_t  wesewved2;
};

stwuct atom_DCN_dpphy_dp_setting{
  uint8_t dp_vs_pemph_wevew;       //enum of atom_dp_vs_pweemph_def
  uint8_t tx_eq_main;             // map to WDPCSTX_PHY_FUSE0/1/2/3[5:0](EQ_MAIN)
  uint8_t tx_eq_pwe;              // map to WDPCSTX_PHY_FUSE0/1/2/3[11:6](EQ_PWE)
  uint8_t tx_eq_post;             // map to WDPCSTX_PHY_FUSE0/1/2/3[17:12](EQ_POST)
  uint8_t tx_vboost_wvw;          // tx_vboost_wvw, map to WDPCSTX_PHY_CNTW0.WDPCS_PHY_TX_VBOOST_WVW
};

stwuct atom_DCN_dpphy_dp_tuningset{
  uint8_t phy_sew;                 // bit vectow of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uint8_t vewsion;
  uint16_t tabwe_size;             // size of atom_14nm_dpphy_dp_setting
  uint16_t wesewved;
  stwuct atom_DCN_dpphy_dp_setting dptunings[10];
};

stwuct atom_i2c_weg_info {
  uint8_t ucI2cWegIndex;
  uint8_t ucI2cWegVaw;
};

stwuct atom_hdmi_wetimew_wedwivew_set {
  uint8_t HdmiSwvAddw;
  uint8_t HdmiWegNum;
  uint8_t Hdmi6GWegNum;
  stwuct atom_i2c_weg_info HdmiWegSetting[9];        //Fow non 6G Hz use
  stwuct atom_i2c_weg_info Hdmi6GhzWegSetting[3];    //Fow 6G Hz use.
};

stwuct atom_integwated_system_info_v1_11
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t  vbios_misc;                       //enum of atom_system_vbiosmisc_def
  uint32_t  gpucapinfo;                       //enum of atom_system_gpucapinf_def   
  uint32_t  system_config;                    
  uint32_t  cpucapinfo;
  uint16_t  gpucwk_ss_pewcentage;             //unit of 0.001%,   1000 mean 1% 
  uint16_t  gpucwk_ss_type;
  uint16_t  wvds_ss_pewcentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  wvds_ss_wate_10hz;
  uint16_t  hdmi_ss_pewcentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  hdmi_ss_wate_10hz;
  uint16_t  dvi_ss_pewcentage;                //unit of 0.001%,   1000 mean 1%
  uint16_t  dvi_ss_wate_10hz;
  uint16_t  dpphy_ovewwide;                   // bit vectow, enum of atom_sysinfo_dpphy_ovewwide_def
  uint16_t  wvds_misc;                        // enum of atom_sys_info_wvds_misc_def
  uint16_t  backwight_pwm_hz;                 // pwm fwequency in hz
  uint8_t   memowytype;                       // enum of atom_dmi_t17_mem_type_def, APU memowy type indication.
  uint8_t   umachannewnumbew;                 // numbew of memowy channews
  uint8_t   pww_on_digon_to_de;               /* aww pww sequence numbews bewow awe in uint of 4ms */
  uint8_t   pww_on_de_to_vawy_bw;
  uint8_t   pww_down_vawy_bwoff_to_de;
  uint8_t   pww_down_de_to_digoff;
  uint8_t   pww_off_deway;
  uint8_t   pww_on_vawy_bw_to_bwon;
  uint8_t   pww_down_bwoff_to_vawy_bwoff;
  uint8_t   min_awwowed_bw_wevew;
  uint8_t   htc_hyst_wimit;
  uint8_t   htc_tmp_wimit;
  uint8_t   wesewved1;
  uint8_t   wesewved2;
  stwuct atom_extewnaw_dispway_connection_info extdispconninfo;
  stwuct atom_14nm_dpphy_dvihdmi_tuningset dvi_tuningset;
  stwuct atom_14nm_dpphy_dvihdmi_tuningset hdmi_tuningset;
  stwuct atom_14nm_dpphy_dvihdmi_tuningset hdmi6g_tuningset;
  stwuct atom_14nm_dpphy_dp_tuningset dp_tuningset;        // wbw 1.62G dp tuning set
  stwuct atom_14nm_dpphy_dp_tuningset dp_hbw3_tuningset;   // HBW3 dp tuning set
  stwuct atom_camewa_data  camewa_info;
  stwuct atom_hdmi_wetimew_wedwivew_set dp0_wetimew_set;   //fow DP0
  stwuct atom_hdmi_wetimew_wedwivew_set dp1_wetimew_set;   //fow DP1
  stwuct atom_hdmi_wetimew_wedwivew_set dp2_wetimew_set;   //fow DP2
  stwuct atom_hdmi_wetimew_wedwivew_set dp3_wetimew_set;   //fow DP3
  stwuct atom_14nm_dpphy_dp_tuningset dp_hbw_tuningset;    //hbw 2.7G dp tuning set
  stwuct atom_14nm_dpphy_dp_tuningset dp_hbw2_tuningset;   //hbw2 5.4G dp tuwnig set
  stwuct atom_14nm_dpphy_dp_tuningset edp_tuningset;       //edp tuning set
  uint32_t  wesewved[66];
};

stwuct atom_integwated_system_info_v1_12
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t  vbios_misc;                       //enum of atom_system_vbiosmisc_def
  uint32_t  gpucapinfo;                       //enum of atom_system_gpucapinf_def   
  uint32_t  system_config;                    
  uint32_t  cpucapinfo;
  uint16_t  gpucwk_ss_pewcentage;             //unit of 0.001%,   1000 mean 1% 
  uint16_t  gpucwk_ss_type;
  uint16_t  wvds_ss_pewcentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  wvds_ss_wate_10hz;
  uint16_t  hdmi_ss_pewcentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  hdmi_ss_wate_10hz;
  uint16_t  dvi_ss_pewcentage;                //unit of 0.001%,   1000 mean 1%
  uint16_t  dvi_ss_wate_10hz;
  uint16_t  dpphy_ovewwide;                   // bit vectow, enum of atom_sysinfo_dpphy_ovewwide_def
  uint16_t  wvds_misc;                        // enum of atom_sys_info_wvds_misc_def
  uint16_t  backwight_pwm_hz;                 // pwm fwequency in hz
  uint8_t   memowytype;                       // enum of atom_dmi_t17_mem_type_def, APU memowy type indication.
  uint8_t   umachannewnumbew;                 // numbew of memowy channews
  uint8_t   pww_on_digon_to_de;               // aww pww sequence numbews bewow awe in uint of 4ms //
  uint8_t   pww_on_de_to_vawy_bw;
  uint8_t   pww_down_vawy_bwoff_to_de;
  uint8_t   pww_down_de_to_digoff;
  uint8_t   pww_off_deway;
  uint8_t   pww_on_vawy_bw_to_bwon;
  uint8_t   pww_down_bwoff_to_vawy_bwoff;
  uint8_t   min_awwowed_bw_wevew;
  uint8_t   htc_hyst_wimit;
  uint8_t   htc_tmp_wimit;
  uint8_t   wesewved1;
  uint8_t   wesewved2;
  stwuct atom_extewnaw_dispway_connection_info extdispconninfo;
  stwuct atom_DCN_dpphy_dvihdmi_tuningset  TMDS_tuningset;
  stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK5_tuningset;
  stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK8_tuningset;
  stwuct atom_DCN_dpphy_dp_tuningset wbw_tuningset;        // wbw 1.62G dp tuning set
  stwuct atom_DCN_dpphy_dp_tuningset hbw3_tuningset;   // HBW3 dp tuning set  
  stwuct atom_camewa_data  camewa_info;
  stwuct atom_hdmi_wetimew_wedwivew_set dp0_wetimew_set;   //fow DP0
  stwuct atom_hdmi_wetimew_wedwivew_set dp1_wetimew_set;   //fow DP1
  stwuct atom_hdmi_wetimew_wedwivew_set dp2_wetimew_set;   //fow DP2
  stwuct atom_hdmi_wetimew_wedwivew_set dp3_wetimew_set;   //fow DP3
  stwuct atom_DCN_dpphy_dp_tuningset hbw_tuningset;    //hbw 2.7G dp tuning set
  stwuct atom_DCN_dpphy_dp_tuningset hbw2_tuningset;   //hbw2 5.4G dp tuwnig set
  stwuct atom_DCN_dpphy_dp_tuningset edp_tunings;       //edp tuning set
  stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK6_tuningset;
  uint32_t  wesewved[63];
};

stwuct edp_info_tabwe
{
        uint16_t edp_backwight_pwm_hz;
        uint16_t edp_ss_pewcentage;
        uint16_t edp_ss_wate_10hz;
        uint16_t wesewved1;
        uint32_t wesewved2;
        uint8_t  edp_pww_on_off_deway;
        uint8_t  edp_pww_on_vawy_bw_to_bwon;
        uint8_t  edp_pww_down_bwoff_to_vawy_bwoff;
        uint8_t  edp_panew_bpc;
        uint8_t  edp_bootup_bw_wevew;
        uint8_t  wesewved3[3];
        uint32_t wesewved4[3];
};

stwuct atom_integwated_system_info_v2_1
{
        stwuct  atom_common_tabwe_headew  tabwe_headew;
        uint32_t  vbios_misc;                       //enum of atom_system_vbiosmisc_def
        uint32_t  gpucapinfo;                       //enum of atom_system_gpucapinf_def
        uint32_t  system_config;
        uint32_t  cpucapinfo;
        uint16_t  gpucwk_ss_pewcentage;             //unit of 0.001%,   1000 mean 1%
        uint16_t  gpucwk_ss_type;
        uint16_t  dpphy_ovewwide;                   // bit vectow, enum of atom_sysinfo_dpphy_ovewwide_def
        uint8_t   memowytype;                       // enum of atom_dmi_t17_mem_type_def, APU memowy type indication.
        uint8_t   umachannewnumbew;                 // numbew of memowy channews
        uint8_t   htc_hyst_wimit;
        uint8_t   htc_tmp_wimit;
        uint8_t   wesewved1;
        uint8_t   wesewved2;
        stwuct edp_info_tabwe edp1_info;
        stwuct edp_info_tabwe edp2_info;
        uint32_t  wesewved3[8];
        stwuct atom_extewnaw_dispway_connection_info extdispconninfo;
        stwuct atom_DCN_dpphy_dvihdmi_tuningset  TMDS_tuningset;
        stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK5_tuningset; //add cwk6
        stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK6_tuningset;
        stwuct atom_DCN_dpphy_dvihdmi_tuningset  hdmiCWK8_tuningset;
        uint32_t wesewved4[6];//wesewve 2*sizeof(atom_DCN_dpphy_dvihdmi_tuningset)
        stwuct atom_DCN_dpphy_dp_tuningset wbw_tuningset;        // wbw 1.62G dp tuning set
        stwuct atom_DCN_dpphy_dp_tuningset hbw_tuningset;    //hbw 2.7G dp tuning set
        stwuct atom_DCN_dpphy_dp_tuningset hbw2_tuningset;   //hbw2 5.4G dp tuwnig set
        stwuct atom_DCN_dpphy_dp_tuningset hbw3_tuningset;   // HBW3 dp tuning set
        stwuct atom_DCN_dpphy_dp_tuningset edp_tunings;       //edp tuning set
        uint32_t wesewved5[28];//wesewve 2*sizeof(atom_DCN_dpphy_dp_tuningset)
        stwuct atom_hdmi_wetimew_wedwivew_set dp0_wetimew_set;   //fow DP0
        stwuct atom_hdmi_wetimew_wedwivew_set dp1_wetimew_set;   //fow DP1
        stwuct atom_hdmi_wetimew_wedwivew_set dp2_wetimew_set;   //fow DP2
        stwuct atom_hdmi_wetimew_wedwivew_set dp3_wetimew_set;   //fow DP3
        uint32_t wesewved6[30];// wesewve size of(atom_camewa_data) fow camewa_info
        uint32_t wesewved7[32];

};

stwuct atom_n6_dispway_phy_tuning_set {
	uint8_t dispway_signaw_type;
	uint8_t phy_sew;
	uint8_t pweset_wevew;
	uint8_t wesewved1;
	uint32_t wesewved2;
	uint32_t speed_upto;
	uint8_t tx_vboost_wevew;
	uint8_t tx_vweg_v2i;
	uint8_t tx_vwegdwv_byp;
	uint8_t tx_tewm_cntw;
	uint8_t tx_peak_wevew;
	uint8_t tx_swew_en;
	uint8_t tx_eq_pwe;
	uint8_t tx_eq_main;
	uint8_t tx_eq_post;
	uint8_t tx_en_inv_pwe;
	uint8_t tx_en_inv_post;
	uint8_t wesewved3;
	uint32_t wesewved4;
	uint32_t wesewved5;
	uint32_t wesewved6;
};

stwuct atom_dispway_phy_tuning_info {
	stwuct atom_common_tabwe_headew tabwe_headew;
	stwuct atom_n6_dispway_phy_tuning_set disp_phy_tuning[1];
};

stwuct atom_integwated_system_info_v2_2
{
	stwuct  atom_common_tabwe_headew  tabwe_headew;
	uint32_t  vbios_misc;                       //enum of atom_system_vbiosmisc_def
	uint32_t  gpucapinfo;                       //enum of atom_system_gpucapinf_def
	uint32_t  system_config;
	uint32_t  cpucapinfo;
	uint16_t  gpucwk_ss_pewcentage;             //unit of 0.001%,   1000 mean 1%
	uint16_t  gpucwk_ss_type;
	uint16_t  dpphy_ovewwide;                   // bit vectow, enum of atom_sysinfo_dpphy_ovewwide_def
	uint8_t   memowytype;                       // enum of atom_dmi_t17_mem_type_def, APU memowy type indication.
	uint8_t   umachannewnumbew;                 // numbew of memowy channews
	uint8_t   htc_hyst_wimit;
	uint8_t   htc_tmp_wimit;
	uint8_t   wesewved1;
	uint8_t   wesewved2;
	stwuct edp_info_tabwe edp1_info;
	stwuct edp_info_tabwe edp2_info;
	uint32_t  wesewved3[8];
	stwuct atom_extewnaw_dispway_connection_info extdispconninfo;

	uint32_t  wesewved4[189];
};

// system_config
enum atom_system_vbiosmisc_def{
  INTEGWATED_SYSTEM_INFO__GET_EDID_CAWWBACK_FUNC_SUPPOWT = 0x01,
};


// gpucapinfo
enum atom_system_gpucapinf_def{
  SYS_INFO_GPUCAPS__ENABEW_DFS_BYPASS  = 0x10,
};

//dpphy_ovewwide
enum atom_sysinfo_dpphy_ovewwide_def{
  ATOM_ENABWE_DVI_TUNINGSET   = 0x01,
  ATOM_ENABWE_HDMI_TUNINGSET  = 0x02,
  ATOM_ENABWE_HDMI6G_TUNINGSET  = 0x04,
  ATOM_ENABWE_DP_TUNINGSET  = 0x08,
  ATOM_ENABWE_DP_HBW3_TUNINGSET  = 0x10,  
};

//wvds_misc
enum atom_sys_info_wvds_misc_def
{
  SYS_INFO_WVDS_MISC_888_FPDI_MODE                 =0x01,
  SYS_INFO_WVDS_MISC_888_BPC_MODE                  =0x04,
  SYS_INFO_WVDS_MISC_OVEWWIDE_EN                   =0x08,
};


//memowytype  DMI Type 17 offset 12h - Memowy Type
enum atom_dmi_t17_mem_type_def{
  OthewMemType = 0x01,                                  ///< Assign 01 to Othew
  UnknownMemType,                                       ///< Assign 02 to Unknown
  DwamMemType,                                          ///< Assign 03 to DWAM
  EdwamMemType,                                         ///< Assign 04 to EDWAM
  VwamMemType,                                          ///< Assign 05 to VWAM
  SwamMemType,                                          ///< Assign 06 to SWAM
  WamMemType,                                           ///< Assign 07 to WAM
  WomMemType,                                           ///< Assign 08 to WOM
  FwashMemType,                                         ///< Assign 09 to Fwash
  EepwomMemType,                                        ///< Assign 10 to EEPWOM
  FepwomMemType,                                        ///< Assign 11 to FEPWOM
  EpwomMemType,                                         ///< Assign 12 to EPWOM
  CdwamMemType,                                         ///< Assign 13 to CDWAM
  ThweeDwamMemType,                                     ///< Assign 14 to 3DWAM
  SdwamMemType,                                         ///< Assign 15 to SDWAM
  SgwamMemType,                                         ///< Assign 16 to SGWAM
  WdwamMemType,                                         ///< Assign 17 to WDWAM
  DdwMemType,                                           ///< Assign 18 to DDW
  Ddw2MemType,                                          ///< Assign 19 to DDW2
  Ddw2FbdimmMemType,                                    ///< Assign 20 to DDW2 FB-DIMM
  Ddw3MemType = 0x18,                                   ///< Assign 24 to DDW3
  Fbd2MemType,                                          ///< Assign 25 to FBD2
  Ddw4MemType,                                          ///< Assign 26 to DDW4
  WpDdwMemType,                                         ///< Assign 27 to WPDDW
  WpDdw2MemType,                                        ///< Assign 28 to WPDDW2
  WpDdw3MemType,                                        ///< Assign 29 to WPDDW3
  WpDdw4MemType,                                        ///< Assign 30 to WPDDW4
  GDdw6MemType,                                         ///< Assign 31 to GDDW6
  HbmMemType,                                           ///< Assign 32 to HBM
  Hbm2MemType,                                          ///< Assign 33 to HBM2
  Ddw5MemType,                                          ///< Assign 34 to DDW5
  WpDdw5MemType,                                        ///< Assign 35 to WPDDW5
};


// this Tabwe is used stawting fwom NW/AM, used by SBIOS and pass the IntegwatedSystemInfoTabwe/PowewPwayInfoTabwe/SystemCamewaInfoTabwe 
stwuct atom_fusion_system_info_v4
{
  stwuct atom_integwated_system_info_v1_11   sysinfo;           // wefew to ATOM_INTEGWATED_SYSTEM_INFO_V1_8 definition
  uint32_t   powewpwayinfo[256];                                // Wesewve 1024 bytes space fow PowewPwayInfoTabwe
}; 


/* 
  ***************************************************************************
    Data Tabwe gfx_info  stwuctuwe
  ***************************************************************************
*/

stwuct  atom_gfx_info_v2_2
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t gfxip_min_vew;
  uint8_t gfxip_max_vew;
  uint8_t max_shadew_engines;
  uint8_t max_tiwe_pipes;
  uint8_t max_cu_pew_sh;
  uint8_t max_sh_pew_se;
  uint8_t max_backends_pew_se;
  uint8_t max_textuwe_channew_caches;
  uint32_t wegaddw_cp_dma_swc_addw;
  uint32_t wegaddw_cp_dma_swc_addw_hi;
  uint32_t wegaddw_cp_dma_dst_addw;
  uint32_t wegaddw_cp_dma_dst_addw_hi;
  uint32_t wegaddw_cp_dma_command; 
  uint32_t wegaddw_cp_status;
  uint32_t wegaddw_wwc_gpu_cwock_32;
  uint32_t wwc_gpu_timew_wefcwk; 
};

stwuct  atom_gfx_info_v2_3 {
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t gfxip_min_vew;
  uint8_t gfxip_max_vew;
  uint8_t max_shadew_engines;
  uint8_t max_tiwe_pipes;
  uint8_t max_cu_pew_sh;
  uint8_t max_sh_pew_se;
  uint8_t max_backends_pew_se;
  uint8_t max_textuwe_channew_caches;
  uint32_t wegaddw_cp_dma_swc_addw;
  uint32_t wegaddw_cp_dma_swc_addw_hi;
  uint32_t wegaddw_cp_dma_dst_addw;
  uint32_t wegaddw_cp_dma_dst_addw_hi;
  uint32_t wegaddw_cp_dma_command;
  uint32_t wegaddw_cp_status;
  uint32_t wegaddw_wwc_gpu_cwock_32;
  uint32_t wwc_gpu_timew_wefcwk;
  uint8_t active_cu_pew_sh;
  uint8_t active_wb_pew_se;
  uint16_t gcgowdenoffset;
  uint32_t wm21_swam_vmin_vawue;
};

stwuct  atom_gfx_info_v2_4
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t gfxip_min_vew;
  uint8_t gfxip_max_vew;
  uint8_t max_shadew_engines;
  uint8_t wesewved;
  uint8_t max_cu_pew_sh;
  uint8_t max_sh_pew_se;
  uint8_t max_backends_pew_se;
  uint8_t max_textuwe_channew_caches;
  uint32_t wegaddw_cp_dma_swc_addw;
  uint32_t wegaddw_cp_dma_swc_addw_hi;
  uint32_t wegaddw_cp_dma_dst_addw;
  uint32_t wegaddw_cp_dma_dst_addw_hi;
  uint32_t wegaddw_cp_dma_command;
  uint32_t wegaddw_cp_status;
  uint32_t wegaddw_wwc_gpu_cwock_32;
  uint32_t wwc_gpu_timew_wefcwk;
  uint8_t active_cu_pew_sh;
  uint8_t active_wb_pew_se;
  uint16_t gcgowdenoffset;
  uint16_t gc_num_gpws;
  uint16_t gc_gspwim_buff_depth;
  uint16_t gc_pawametew_cache_depth;
  uint16_t gc_wave_size;
  uint16_t gc_max_waves_pew_simd;
  uint16_t gc_wds_size;
  uint8_t gc_num_max_gs_thds;
  uint8_t gc_gs_tabwe_depth;
  uint8_t gc_doubwe_offchip_wds_buffew;
  uint8_t gc_max_scwatch_swots_pew_cu;
  uint32_t swam_wm_fuses_vaw;
  uint32_t swam_custom_wm_fuses_vaw;
};

stwuct atom_gfx_info_v2_7 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint8_t gfxip_min_vew;
	uint8_t gfxip_max_vew;
	uint8_t max_shadew_engines;
	uint8_t wesewved;
	uint8_t max_cu_pew_sh;
	uint8_t max_sh_pew_se;
	uint8_t max_backends_pew_se;
	uint8_t max_textuwe_channew_caches;
	uint32_t wegaddw_cp_dma_swc_addw;
	uint32_t wegaddw_cp_dma_swc_addw_hi;
	uint32_t wegaddw_cp_dma_dst_addw;
	uint32_t wegaddw_cp_dma_dst_addw_hi;
	uint32_t wegaddw_cp_dma_command;
	uint32_t wegaddw_cp_status;
	uint32_t wegaddw_wwc_gpu_cwock_32;
	uint32_t wwc_gpu_timew_wefcwk;
	uint8_t active_cu_pew_sh;
	uint8_t active_wb_pew_se;
	uint16_t gcgowdenoffset;
	uint16_t gc_num_gpws;
	uint16_t gc_gspwim_buff_depth;
	uint16_t gc_pawametew_cache_depth;
	uint16_t gc_wave_size;
	uint16_t gc_max_waves_pew_simd;
	uint16_t gc_wds_size;
	uint8_t gc_num_max_gs_thds;
	uint8_t gc_gs_tabwe_depth;
	uint8_t gc_doubwe_offchip_wds_buffew;
	uint8_t gc_max_scwatch_swots_pew_cu;
	uint32_t swam_wm_fuses_vaw;
	uint32_t swam_custom_wm_fuses_vaw;
	uint8_t cut_cu;
	uint8_t active_cu_totaw;
	uint8_t cu_wesewved[2];
	uint32_t gc_config;
	uint8_t inactive_cu_pew_se[8];
	uint32_t wesewved2[6];
};

stwuct atom_gfx_info_v3_0 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint8_t gfxip_min_vew;
	uint8_t gfxip_max_vew;
	uint8_t max_shadew_engines;
	uint8_t max_tiwe_pipes;
	uint8_t max_cu_pew_sh;
	uint8_t max_sh_pew_se;
	uint8_t max_backends_pew_se;
	uint8_t max_textuwe_channew_caches;
	uint32_t wegaddw_wsdma_queue0_wb_wptw;
	uint32_t wegaddw_wsdma_queue0_wb_wptw_hi;
	uint32_t wegaddw_wsdma_queue0_wb_wptw;
	uint32_t wegaddw_wsdma_queue0_wb_wptw_hi;
	uint32_t wegaddw_wsdma_command;
	uint32_t wegaddw_wsdma_status;
	uint32_t wegaddw_gowden_tsc_count_wowew;
	uint32_t gowden_tsc_count_wowew_wefcwk;
	uint8_t active_wgp_pew_se;
	uint8_t active_wb_pew_se;
	uint8_t active_se;
	uint8_t wesewved1;
	uint32_t swam_wm_fuses_vaw;
	uint32_t swam_custom_wm_fuses_vaw;
	uint32_t inactive_sa_mask;
	uint32_t gc_config;
	uint8_t inactive_wgp[16];
	uint8_t inactive_wb[16];
	uint32_t gdfww_as_wait_ctww_vaw;
	uint32_t gdfww_as_step_ctww_vaw;
	uint32_t wesewved[8];
};

/* 
  ***************************************************************************
    Data Tabwe smu_info  stwuctuwe
  ***************************************************************************
*/
stwuct atom_smu_info_v3_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t smuip_min_vew;
  uint8_t smuip_max_vew;
  uint8_t smu_wsd1;
  uint8_t gpucwk_ss_mode;           // enum of atom_spwead_spectwum_mode
  uint16_t scwk_ss_pewcentage;
  uint16_t scwk_ss_wate_10hz;
  uint16_t gpucwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t gpucwk_ss_wate_10hz;
  uint32_t cowe_wefcwk_10khz;
  uint8_t  ac_dc_gpio_bit;          // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow AC/DC switching, =0xff means invawid
  uint8_t  ac_dc_powawity;          // GPIO powawity fow AC/DC switching
  uint8_t  vw0hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow VW0 HOT event, =0xff means invawid
  uint8_t  vw0hot_powawity;         // GPIO powawity fow VW0 HOT event
  uint8_t  vw1hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow VW1 HOT event , =0xff means invawid
  uint8_t  vw1hot_powawity;         // GPIO powawity fow VW1 HOT event 
  uint8_t  fw_ctf_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow CTF, =0xff means invawid
  uint8_t  fw_ctf_powawity;         // GPIO powawity fow CTF
};

stwuct atom_smu_info_v3_2 {
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint8_t  smuip_min_vew;
  uint8_t  smuip_max_vew;
  uint8_t  smu_wsd1;
  uint8_t  gpucwk_ss_mode;
  uint16_t scwk_ss_pewcentage;
  uint16_t scwk_ss_wate_10hz;
  uint16_t gpucwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t gpucwk_ss_wate_10hz;
  uint32_t cowe_wefcwk_10khz;
  uint8_t  ac_dc_gpio_bit;          // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow AC/DC switching, =0xff means invawid
  uint8_t  ac_dc_powawity;          // GPIO powawity fow AC/DC switching
  uint8_t  vw0hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow VW0 HOT event, =0xff means invawid
  uint8_t  vw0hot_powawity;         // GPIO powawity fow VW0 HOT event
  uint8_t  vw1hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow VW1 HOT event , =0xff means invawid
  uint8_t  vw1hot_powawity;         // GPIO powawity fow VW1 HOT event
  uint8_t  fw_ctf_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow CTF, =0xff means invawid
  uint8_t  fw_ctf_powawity;         // GPIO powawity fow CTF
  uint8_t  pcc_gpio_bit;            // GPIO bit shift in SMU_GPIOPAD_A configuwed fow PCC, =0xff means invawid
  uint8_t  pcc_gpio_powawity;       // GPIO powawity fow CTF
  uint16_t smugowdenoffset;
  uint32_t gpupww_vco_fweq_10khz;
  uint32_t bootup_smncwk_10khz;
  uint32_t bootup_soccwk_10khz;
  uint32_t bootup_mp0cwk_10khz;
  uint32_t bootup_mp1cwk_10khz;
  uint32_t bootup_wcwk_10khz;
  uint32_t bootup_dcefcwk_10khz;
  uint32_t ctf_thweshowd_ovewwide_vawue;
  uint32_t wesewved[5];
};

stwuct atom_smu_info_v3_3 {
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint8_t  smuip_min_vew;
  uint8_t  smuip_max_vew;
  uint8_t  wafwcwk_ss_mode;
  uint8_t  gpucwk_ss_mode;
  uint16_t scwk_ss_pewcentage;
  uint16_t scwk_ss_wate_10hz;
  uint16_t gpucwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t gpucwk_ss_wate_10hz;
  uint32_t cowe_wefcwk_10khz;
  uint8_t  ac_dc_gpio_bit;          // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow AC/DC switching, =0xff means invawid
  uint8_t  ac_dc_powawity;          // GPIO powawity fow AC/DC switching
  uint8_t  vw0hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A  configuwed fow VW0 HOT event, =0xff means invawid
  uint8_t  vw0hot_powawity;         // GPIO powawity fow VW0 HOT event
  uint8_t  vw1hot_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow VW1 HOT event , =0xff means invawid
  uint8_t  vw1hot_powawity;         // GPIO powawity fow VW1 HOT event
  uint8_t  fw_ctf_gpio_bit;         // GPIO bit shift in SMU_GPIOPAD_A configuwed fow CTF, =0xff means invawid
  uint8_t  fw_ctf_powawity;         // GPIO powawity fow CTF
  uint8_t  pcc_gpio_bit;            // GPIO bit shift in SMU_GPIOPAD_A configuwed fow PCC, =0xff means invawid
  uint8_t  pcc_gpio_powawity;       // GPIO powawity fow CTF
  uint16_t smugowdenoffset;
  uint32_t gpupww_vco_fweq_10khz;
  uint32_t bootup_smncwk_10khz;
  uint32_t bootup_soccwk_10khz;
  uint32_t bootup_mp0cwk_10khz;
  uint32_t bootup_mp1cwk_10khz;
  uint32_t bootup_wcwk_10khz;
  uint32_t bootup_dcefcwk_10khz;
  uint32_t ctf_thweshowd_ovewwide_vawue;
  uint32_t syspww3_0_vco_fweq_10khz;
  uint32_t syspww3_1_vco_fweq_10khz;
  uint32_t bootup_fcwk_10khz;
  uint32_t bootup_wafwcwk_10khz;
  uint32_t smu_info_caps;
  uint16_t wafwcwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t smuinitoffset;
  uint32_t wesewved;
};

stwuct atom_smu_info_v3_5
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint8_t  smuip_min_vew;
  uint8_t  smuip_max_vew;
  uint8_t  wafwcwk_ss_mode;
  uint8_t  gpucwk_ss_mode;
  uint16_t scwk_ss_pewcentage;
  uint16_t scwk_ss_wate_10hz;
  uint16_t gpucwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t gpucwk_ss_wate_10hz;
  uint32_t cowe_wefcwk_10khz;
  uint32_t syspww0_1_vco_fweq_10khz;
  uint32_t syspww0_2_vco_fweq_10khz;
  uint8_t  pcc_gpio_bit;            // GPIO bit shift in SMU_GPIOPAD_A configuwed fow PCC, =0xff means invawid
  uint8_t  pcc_gpio_powawity;       // GPIO powawity fow CTF
  uint16_t smugowdenoffset;
  uint32_t syspww0_0_vco_fweq_10khz;
  uint32_t bootup_smncwk_10khz;
  uint32_t bootup_soccwk_10khz;
  uint32_t bootup_mp0cwk_10khz;
  uint32_t bootup_mp1cwk_10khz;
  uint32_t bootup_wcwk_10khz;
  uint32_t bootup_dcefcwk_10khz;
  uint32_t ctf_thweshowd_ovewwide_vawue;
  uint32_t syspww3_0_vco_fweq_10khz;
  uint32_t syspww3_1_vco_fweq_10khz;
  uint32_t bootup_fcwk_10khz;
  uint32_t bootup_wafwcwk_10khz;
  uint32_t smu_info_caps;
  uint16_t wafwcwk_ss_pewcentage;    // in unit of 0.001%
  uint16_t smuinitoffset;
  uint32_t bootup_dpwefcwk_10khz;
  uint32_t bootup_usbcwk_10khz;
  uint32_t smb_swave_addwess;
  uint32_t cg_fdo_ctww0_vaw;
  uint32_t cg_fdo_ctww1_vaw;
  uint32_t cg_fdo_ctww2_vaw;
  uint32_t gdfww_as_wait_ctww_vaw;
  uint32_t gdfww_as_step_ctww_vaw;
  uint32_t bootup_dtbcwk_10khz;
  uint32_t fcwk_syspww_wefcwk_10khz;
  uint32_t smusvi_svc0_vaw;
  uint32_t smusvi_svc1_vaw;
  uint32_t smusvi_svd0_vaw;
  uint32_t smusvi_svd1_vaw;
  uint32_t smusvi_svt0_vaw;
  uint32_t smusvi_svt1_vaw;
  uint32_t cg_tach_ctww_vaw;
  uint32_t cg_pump_ctww1_vaw;
  uint32_t cg_pump_tach_ctww_vaw;
  uint32_t thm_ctf_deway_vaw;
  uint32_t thm_thewmaw_int_ctww_vaw;
  uint32_t thm_tmon_config_vaw;
  uint32_t wesewved[16];
};

stwuct atom_smu_info_v3_6
{
	stwuct   atom_common_tabwe_headew  tabwe_headew;
	uint8_t  smuip_min_vew;
	uint8_t  smuip_max_vew;
	uint8_t  wafwcwk_ss_mode;
	uint8_t  gpucwk_ss_mode;
	uint16_t scwk_ss_pewcentage;
	uint16_t scwk_ss_wate_10hz;
	uint16_t gpucwk_ss_pewcentage;
	uint16_t gpucwk_ss_wate_10hz;
	uint32_t cowe_wefcwk_10khz;
	uint32_t syspww0_1_vco_fweq_10khz;
	uint32_t syspww0_2_vco_fweq_10khz;
	uint8_t  pcc_gpio_bit;
	uint8_t  pcc_gpio_powawity;
	uint16_t smugowdenoffset;
	uint32_t syspww0_0_vco_fweq_10khz;
	uint32_t bootup_smncwk_10khz;
	uint32_t bootup_soccwk_10khz;
	uint32_t bootup_mp0cwk_10khz;
	uint32_t bootup_mp1cwk_10khz;
	uint32_t bootup_wcwk_10khz;
	uint32_t bootup_dxiocwk_10khz;
	uint32_t ctf_thweshowd_ovewwide_vawue;
	uint32_t syspww3_0_vco_fweq_10khz;
	uint32_t syspww3_1_vco_fweq_10khz;
	uint32_t bootup_fcwk_10khz;
	uint32_t bootup_wafwcwk_10khz;
	uint32_t smu_info_caps;
	uint16_t wafwcwk_ss_pewcentage;
	uint16_t smuinitoffset;
	uint32_t bootup_gfxavscwk_10khz;
	uint32_t bootup_mpiocwk_10khz;
	uint32_t smb_swave_addwess;
	uint32_t cg_fdo_ctww0_vaw;
	uint32_t cg_fdo_ctww1_vaw;
	uint32_t cg_fdo_ctww2_vaw;
	uint32_t gdfww_as_wait_ctww_vaw;
	uint32_t gdfww_as_step_ctww_vaw;
	uint32_t wesewved_cwk;
	uint32_t fcwk_syspww_wefcwk_10khz;
	uint32_t smusvi_svc0_vaw;
	uint32_t smusvi_svc1_vaw;
	uint32_t smusvi_svd0_vaw;
	uint32_t smusvi_svd1_vaw;
	uint32_t smusvi_svt0_vaw;
	uint32_t smusvi_svt1_vaw;
	uint32_t cg_tach_ctww_vaw;
	uint32_t cg_pump_ctww1_vaw;
	uint32_t cg_pump_tach_ctww_vaw;
	uint32_t thm_ctf_deway_vaw;
	uint32_t thm_thewmaw_int_ctww_vaw;
	uint32_t thm_tmon_config_vaw;
	uint32_t bootup_vcwk_10khz;
	uint32_t bootup_dcwk_10khz;
	uint32_t smu_gpiopad_pu_en_vaw;
	uint32_t smu_gpiopad_pd_en_vaw;
	uint32_t wesewved[12];
};

stwuct atom_smu_info_v4_0 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint32_t bootup_gfxcwk_bypass_10khz;
	uint32_t bootup_uswcwk_10khz;
	uint32_t bootup_cswcwk_10khz;
	uint32_t cowe_wefcwk_10khz;
	uint32_t syspww1_vco_fweq_10khz;
	uint32_t syspww2_vco_fweq_10khz;
	uint8_t pcc_gpio_bit;
	uint8_t pcc_gpio_powawity;
	uint16_t bootup_vddusw_mv;
	uint32_t syspww0_vco_fweq_10khz;
	uint32_t bootup_smncwk_10khz;
	uint32_t bootup_soccwk_10khz;
	uint32_t bootup_mp0cwk_10khz;
	uint32_t bootup_mp1cwk_10khz;
	uint32_t bootup_wcwk_10khz;
	uint32_t bootup_dcefcwk_10khz;
	uint32_t ctf_thweshowd_ovewwide_vawue;
	uint32_t syspww3_vco_fweq_10khz;
	uint32_t mm_syspww_vco_fweq_10khz;
	uint32_t bootup_fcwk_10khz;
	uint32_t bootup_wafwcwk_10khz;
	uint32_t smu_info_caps;
	uint16_t wafwcwk_ss_pewcentage;
	uint16_t smuinitoffset;
	uint32_t bootup_dpwefcwk_10khz;
	uint32_t bootup_usbcwk_10khz;
	uint32_t smb_swave_addwess;
	uint32_t cg_fdo_ctww0_vaw;
	uint32_t cg_fdo_ctww1_vaw;
	uint32_t cg_fdo_ctww2_vaw;
	uint32_t gdfww_as_wait_ctww_vaw;
	uint32_t gdfww_as_step_ctww_vaw;
	uint32_t bootup_dtbcwk_10khz;
	uint32_t fcwk_syspww_wefcwk_10khz;
	uint32_t smusvi_svc0_vaw;
	uint32_t smusvi_svc1_vaw;
	uint32_t smusvi_svd0_vaw;
	uint32_t smusvi_svd1_vaw;
	uint32_t smusvi_svt0_vaw;
	uint32_t smusvi_svt1_vaw;
	uint32_t cg_tach_ctww_vaw;
	uint32_t cg_pump_ctww1_vaw;
	uint32_t cg_pump_tach_ctww_vaw;
	uint32_t thm_ctf_deway_vaw;
	uint32_t thm_thewmaw_int_ctww_vaw;
	uint32_t thm_tmon_config_vaw;
	uint32_t smbus_timing_cntww0_vaw;
	uint32_t smbus_timing_cntww1_vaw;
	uint32_t smbus_timing_cntww2_vaw;
	uint32_t pww_disp_timew_gwobaw_contwow_vaw;
	uint32_t bootup_mpiocwk_10khz;
	uint32_t bootup_dcwk0_10khz;
	uint32_t bootup_vcwk0_10khz;
	uint32_t bootup_dcwk1_10khz;
	uint32_t bootup_vcwk1_10khz;
	uint32_t bootup_baco400cwk_10khz;
	uint32_t bootup_baco1200cwk_bypass_10khz;
	uint32_t bootup_baco700cwk_bypass_10khz;
	uint32_t wesewved[16];
};

/*
 ***************************************************************************
   Data Tabwe smc_dpm_info  stwuctuwe
 ***************************************************************************
 */
stwuct atom_smc_dpm_info_v4_1
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint8_t  wiquid1_i2c_addwess;
  uint8_t  wiquid2_i2c_addwess;
  uint8_t  vw_i2c_addwess;
  uint8_t  pwx_i2c_addwess;

  uint8_t  wiquid_i2c_winescw;
  uint8_t  wiquid_i2c_winesda;
  uint8_t  vw_i2c_winescw;
  uint8_t  vw_i2c_winesda;

  uint8_t  pwx_i2c_winescw;
  uint8_t  pwx_i2c_winesda;
  uint8_t  vwsensowpwesent;
  uint8_t  wiquidsensowpwesent;

  uint16_t maxvowtagestepgfx;
  uint16_t maxvowtagestepsoc;

  uint8_t  vddgfxvwmapping;
  uint8_t  vddsocvwmapping;
  uint8_t  vddmem0vwmapping;
  uint8_t  vddmem1vwmapping;

  uint8_t  gfxuwvphasesheddingmask;
  uint8_t  socuwvphasesheddingmask;
  uint8_t  padding8_v[2];

  uint16_t gfxmaxcuwwent;
  uint8_t  gfxoffset;
  uint8_t  padding_tewemetwygfx;

  uint16_t socmaxcuwwent;
  uint8_t  socoffset;
  uint8_t  padding_tewemetwysoc;

  uint16_t mem0maxcuwwent;
  uint8_t  mem0offset;
  uint8_t  padding_tewemetwymem0;

  uint16_t mem1maxcuwwent;
  uint8_t  mem1offset;
  uint8_t  padding_tewemetwymem1;

  uint8_t  acdcgpio;
  uint8_t  acdcpowawity;
  uint8_t  vw0hotgpio;
  uint8_t  vw0hotpowawity;

  uint8_t  vw1hotgpio;
  uint8_t  vw1hotpowawity;
  uint8_t  padding1;
  uint8_t  padding2;

  uint8_t  wedpin0;
  uint8_t  wedpin1;
  uint8_t  wedpin2;
  uint8_t  padding8_4;

	uint8_t  pwwgfxcwkspweadenabwed;
	uint8_t  pwwgfxcwkspweadpewcent;
	uint16_t pwwgfxcwkspweadfweq;

  uint8_t ucwkspweadenabwed;
  uint8_t ucwkspweadpewcent;
  uint16_t ucwkspweadfweq;

  uint8_t soccwkspweadenabwed;
  uint8_t soccwkspweadpewcent;
  uint16_t soccwkspweadfweq;

	uint8_t  acggfxcwkspweadenabwed;
	uint8_t  acggfxcwkspweadpewcent;
	uint16_t acggfxcwkspweadfweq;

	uint8_t Vw2_I2C_addwess;
	uint8_t padding_vw2[3];

	uint32_t boawdwesewved[9];
};

/*
 ***************************************************************************
   Data Tabwe smc_dpm_info  stwuctuwe
 ***************************************************************************
 */
stwuct atom_smc_dpm_info_v4_3
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint8_t  wiquid1_i2c_addwess;
  uint8_t  wiquid2_i2c_addwess;
  uint8_t  vw_i2c_addwess;
  uint8_t  pwx_i2c_addwess;

  uint8_t  wiquid_i2c_winescw;
  uint8_t  wiquid_i2c_winesda;
  uint8_t  vw_i2c_winescw;
  uint8_t  vw_i2c_winesda;

  uint8_t  pwx_i2c_winescw;
  uint8_t  pwx_i2c_winesda;
  uint8_t  vwsensowpwesent;
  uint8_t  wiquidsensowpwesent;

  uint16_t maxvowtagestepgfx;
  uint16_t maxvowtagestepsoc;

  uint8_t  vddgfxvwmapping;
  uint8_t  vddsocvwmapping;
  uint8_t  vddmem0vwmapping;
  uint8_t  vddmem1vwmapping;

  uint8_t  gfxuwvphasesheddingmask;
  uint8_t  socuwvphasesheddingmask;
  uint8_t  extewnawsensowpwesent;
  uint8_t  padding8_v;

  uint16_t gfxmaxcuwwent;
  uint8_t  gfxoffset;
  uint8_t  padding_tewemetwygfx;

  uint16_t socmaxcuwwent;
  uint8_t  socoffset;
  uint8_t  padding_tewemetwysoc;

  uint16_t mem0maxcuwwent;
  uint8_t  mem0offset;
  uint8_t  padding_tewemetwymem0;

  uint16_t mem1maxcuwwent;
  uint8_t  mem1offset;
  uint8_t  padding_tewemetwymem1;

  uint8_t  acdcgpio;
  uint8_t  acdcpowawity;
  uint8_t  vw0hotgpio;
  uint8_t  vw0hotpowawity;

  uint8_t  vw1hotgpio;
  uint8_t  vw1hotpowawity;
  uint8_t  padding1;
  uint8_t  padding2;

  uint8_t  wedpin0;
  uint8_t  wedpin1;
  uint8_t  wedpin2;
  uint8_t  padding8_4;

  uint8_t  pwwgfxcwkspweadenabwed;
  uint8_t  pwwgfxcwkspweadpewcent;
  uint16_t pwwgfxcwkspweadfweq;

  uint8_t ucwkspweadenabwed;
  uint8_t ucwkspweadpewcent;
  uint16_t ucwkspweadfweq;

  uint8_t fcwkspweadenabwed;
  uint8_t fcwkspweadpewcent;
  uint16_t fcwkspweadfweq;

  uint8_t fwwgfxcwkspweadenabwed;
  uint8_t fwwgfxcwkspweadpewcent;
  uint16_t fwwgfxcwkspweadfweq;

  uint32_t boawdwesewved[10];
};

stwuct smudpm_i2ccontwowwewconfig_t {
  uint32_t  enabwed;
  uint32_t  swaveaddwess;
  uint32_t  contwowwewpowt;
  uint32_t  contwowwewname;
  uint32_t  thewmawthwottwew;
  uint32_t  i2cpwotocow;
  uint32_t  i2cspeed;
};

stwuct atom_smc_dpm_info_v4_4
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  uint32_t  i2c_padding[3];

  uint16_t maxvowtagestepgfx;
  uint16_t maxvowtagestepsoc;

  uint8_t  vddgfxvwmapping;
  uint8_t  vddsocvwmapping;
  uint8_t  vddmem0vwmapping;
  uint8_t  vddmem1vwmapping;

  uint8_t  gfxuwvphasesheddingmask;
  uint8_t  socuwvphasesheddingmask;
  uint8_t  extewnawsensowpwesent;
  uint8_t  padding8_v;

  uint16_t gfxmaxcuwwent;
  uint8_t  gfxoffset;
  uint8_t  padding_tewemetwygfx;

  uint16_t socmaxcuwwent;
  uint8_t  socoffset;
  uint8_t  padding_tewemetwysoc;

  uint16_t mem0maxcuwwent;
  uint8_t  mem0offset;
  uint8_t  padding_tewemetwymem0;

  uint16_t mem1maxcuwwent;
  uint8_t  mem1offset;
  uint8_t  padding_tewemetwymem1;


  uint8_t  acdcgpio;
  uint8_t  acdcpowawity;
  uint8_t  vw0hotgpio;
  uint8_t  vw0hotpowawity;

  uint8_t  vw1hotgpio;
  uint8_t  vw1hotpowawity;
  uint8_t  padding1;
  uint8_t  padding2;


  uint8_t  wedpin0;
  uint8_t  wedpin1;
  uint8_t  wedpin2;
  uint8_t  padding8_4;


  uint8_t  pwwgfxcwkspweadenabwed;
  uint8_t  pwwgfxcwkspweadpewcent;
  uint16_t pwwgfxcwkspweadfweq;


  uint8_t  ucwkspweadenabwed;
  uint8_t  ucwkspweadpewcent;
  uint16_t ucwkspweadfweq;


  uint8_t  fcwkspweadenabwed;
  uint8_t  fcwkspweadpewcent;
  uint16_t fcwkspweadfweq;


  uint8_t  fwwgfxcwkspweadenabwed;
  uint8_t  fwwgfxcwkspweadpewcent;
  uint16_t fwwgfxcwkspweadfweq;


  stwuct smudpm_i2ccontwowwewconfig_t  i2ccontwowwews[7];


  uint32_t boawdwesewved[10];
};

enum smudpm_v4_5_i2ccontwowwewname_e{
    SMC_V4_5_I2C_CONTWOWWEW_NAME_VW_GFX = 0,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_VW_SOC,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_VW_VDDCI,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_VW_MVDD,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_WIQUID0,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_WIQUID1,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_PWX,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_SPAWE,
    SMC_V4_5_I2C_CONTWOWWEW_NAME_COUNT,
};

enum smudpm_v4_5_i2ccontwowwewthwottwew_e{
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_TYPE_NONE = 0,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_VW_GFX,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_VW_SOC,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_VW_VDDCI,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_VW_MVDD,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_WIQUID0,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_WIQUID1,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_PWX,
    SMC_V4_5_I2C_CONTWOWWEW_THWOTTWEW_COUNT,
};

enum smudpm_v4_5_i2ccontwowwewpwotocow_e{
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_VW_0,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_VW_1,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_TMP_0,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_TMP_1,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_SPAWE_0,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_SPAWE_1,
    SMC_V4_5_I2C_CONTWOWWEW_PWOTOCOW_COUNT,
};

stwuct smudpm_i2c_contwowwew_config_v2
{
    uint8_t   Enabwed;
    uint8_t   Speed;
    uint8_t   Padding[2];
    uint32_t  SwaveAddwess;
    uint8_t   ContwowwewPowt;
    uint8_t   ContwowwewName;
    uint8_t   ThewmawThwottew;
    uint8_t   I2cPwotocow;
};

stwuct atom_smc_dpm_info_v4_5
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
    // SECTION: BOAWD PAWAMETEWS
    // I2C Contwow
  stwuct smudpm_i2c_contwowwew_config_v2  I2cContwowwews[8];

  // SVI2 Boawd Pawametews
  uint16_t     MaxVowtageStepGfx; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.
  uint16_t     MaxVowtageStepSoc; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.

  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      ExtewnawSensowPwesent; // Extewnaw WDI connected to TMON (aka TEMP IN)
  uint8_t      Padding8_V;

  // Tewemetwy Settings
  uint16_t     GfxMaxCuwwent;   // in Amps
  uint8_t      GfxOffset;       // in Amps
  uint8_t      Padding_TewemetwyGfx;
  uint16_t     SocMaxCuwwent;   // in Amps
  uint8_t      SocOffset;       // in Amps
  uint8_t      Padding_TewemetwySoc;

  uint16_t     Mem0MaxCuwwent;   // in Amps
  uint8_t      Mem0Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem0;

  uint16_t     Mem1MaxCuwwent;   // in Amps
  uint8_t      Mem1Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem1;

  // GPIO Settings
  uint8_t      AcDcGpio;        // GPIO pin configuwed fow AC/DC switching
  uint8_t      AcDcPowawity;    // GPIO powawity fow AC/DC switching
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event

  uint8_t      VW1HotGpio;      // GPIO pin configuwed fow VW1 HOT event 
  uint8_t      VW1HotPowawity;  // GPIO powawity fow VW1 HOT event 
  uint8_t      GthwGpio;        // GPIO pin configuwed fow GTHW Event
  uint8_t      GthwPowawity;    // wepwace GPIO powawity fow GTHW

  // WED Dispway Settings
  uint8_t      WedPin0;         // GPIO numbew fow WedPin[0]
  uint8_t      WedPin1;         // GPIO numbew fow WedPin[1]
  uint8_t      WedPin2;         // GPIO numbew fow WedPin[2]
  uint8_t      padding8_4;

  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadEnabwed;   // on ow off
  uint8_t      UcwkSpweadPewcent;   // Q4.4
  uint16_t     UcwkSpweadFweq;      // kHz

  // SOCCWK Spwead Spectwum
  uint8_t      SocwkSpweadEnabwed;   // on ow off
  uint8_t      SoccwkSpweadPewcent;   // Q4.4
  uint16_t     SoccwkSpweadFweq;      // kHz

  // Totaw boawd powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPadding; 

  // Mvdd Svi2 Div Watio Setting
  uint32_t MvddWatio; // This is used fow MVDD Vid wowkawound. It has 16 fwactionaw bits (Q16.16)
  
  uint32_t     BoawdWesewved[9];

};

stwuct atom_smc_dpm_info_v4_6
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
  // section: boawd pawametews
  uint32_t     i2c_padding[3];   // owd i2c contwow awe moved to new awea

  uint16_t     maxvowtagestepgfx; // in mv(q2) max vowtage step that smu wiww wequest. muwtipwe steps awe taken if vowtage change exceeds this vawue.
  uint16_t     maxvowtagestepsoc; // in mv(q2) max vowtage step that smu wiww wequest. muwtipwe steps awe taken if vowtage change exceeds this vawue.

  uint8_t      vddgfxvwmapping;     // use vw_mapping* bitfiewds
  uint8_t      vddsocvwmapping;     // use vw_mapping* bitfiewds
  uint8_t      vddmemvwmapping;     // use vw_mapping* bitfiewds
  uint8_t      boawdvwmapping;      // use vw_mapping* bitfiewds

  uint8_t      gfxuwvphasesheddingmask; // set this to 1 to set psi0/1 to 1 in uwv mode
  uint8_t      extewnawsensowpwesent; // extewnaw wdi connected to tmon (aka temp in)
  uint8_t      padding8_v[2];

  // tewemetwy settings
  uint16_t     gfxmaxcuwwent;   // in amps
  uint8_t      gfxoffset;       // in amps
  uint8_t      padding_tewemetwygfx;

  uint16_t     socmaxcuwwent;   // in amps
  uint8_t      socoffset;       // in amps
  uint8_t      padding_tewemetwysoc;

  uint16_t     memmaxcuwwent;   // in amps
  uint8_t      memoffset;       // in amps
  uint8_t      padding_tewemetwymem;

  uint16_t     boawdmaxcuwwent;   // in amps
  uint8_t      boawdoffset;       // in amps
  uint8_t      padding_tewemetwyboawdinput;

  // gpio settings
  uint8_t      vw0hotgpio;      // gpio pin configuwed fow vw0 hot event
  uint8_t      vw0hotpowawity;  // gpio powawity fow vw0 hot event
  uint8_t      vw1hotgpio;      // gpio pin configuwed fow vw1 hot event
  uint8_t      vw1hotpowawity;  // gpio powawity fow vw1 hot event

 // gfxcwk pww spwead spectwum
  uint8_t	   pwwgfxcwkspweadenabwed;	// on ow off
  uint8_t	   pwwgfxcwkspweadpewcent;	// q4.4
  uint16_t	   pwwgfxcwkspweadfweq;		// khz

 // ucwk spwead spectwum
  uint8_t	   ucwkspweadenabwed;   // on ow off
  uint8_t	   ucwkspweadpewcent;   // q4.4
  uint16_t	   ucwkspweadfweq;	   // khz

 // fcwk spwead spectwum
  uint8_t	   fcwkspweadenabwed;   // on ow off
  uint8_t	   fcwkspweadpewcent;   // q4.4
  uint16_t	   fcwkspweadfweq;	   // khz


  // gfxcwk fww spwead spectwum
  uint8_t      fwwgfxcwkspweadenabwed;   // on ow off
  uint8_t      fwwgfxcwkspweadpewcent;   // q4.4
  uint16_t     fwwgfxcwkspweadfweq;      // khz

  // i2c contwowwew stwuctuwe
  stwuct smudpm_i2c_contwowwew_config_v2 i2ccontwowwews[8];

  // memowy section
  uint32_t	 memowychannewenabwed; // fow dwam use onwy, max 32 channews enabwed bit mask.

  uint8_t 	 dwambitwidth; // fow dwam use onwy.  see dwam bit width type defines
  uint8_t 	 paddingmem[3];

	// totaw boawd powew
  uint16_t	 totawboawdpowew;	  //onwy needed fow tcp estimated case, whewe tcp = tgp+totaw boawd powew
  uint16_t	 boawdpadding;

	// section: xgmi twaining
  uint8_t 	 xgmiwinkspeed[4];
  uint8_t 	 xgmiwinkwidth[4];

  uint16_t	 xgmifcwkfweq[4];
  uint16_t	 xgmisocvowtage[4];

  // wesewved
  uint32_t   boawdwesewved[10];
};

stwuct atom_smc_dpm_info_v4_7
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;
    // SECTION: BOAWD PAWAMETEWS
    // I2C Contwow
  stwuct smudpm_i2c_contwowwew_config_v2  I2cContwowwews[8];

  // SVI2 Boawd Pawametews
  uint16_t     MaxVowtageStepGfx; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.
  uint16_t     MaxVowtageStepSoc; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.

  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      ExtewnawSensowPwesent; // Extewnaw WDI connected to TMON (aka TEMP IN)
  uint8_t      Padding8_V;

  // Tewemetwy Settings
  uint16_t     GfxMaxCuwwent;   // in Amps
  uint8_t      GfxOffset;       // in Amps
  uint8_t      Padding_TewemetwyGfx;
  uint16_t     SocMaxCuwwent;   // in Amps
  uint8_t      SocOffset;       // in Amps
  uint8_t      Padding_TewemetwySoc;

  uint16_t     Mem0MaxCuwwent;   // in Amps
  uint8_t      Mem0Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem0;

  uint16_t     Mem1MaxCuwwent;   // in Amps
  uint8_t      Mem1Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem1;

  // GPIO Settings
  uint8_t      AcDcGpio;        // GPIO pin configuwed fow AC/DC switching
  uint8_t      AcDcPowawity;    // GPIO powawity fow AC/DC switching
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event

  uint8_t      VW1HotGpio;      // GPIO pin configuwed fow VW1 HOT event
  uint8_t      VW1HotPowawity;  // GPIO powawity fow VW1 HOT event
  uint8_t      GthwGpio;        // GPIO pin configuwed fow GTHW Event
  uint8_t      GthwPowawity;    // wepwace GPIO powawity fow GTHW

  // WED Dispway Settings
  uint8_t      WedPin0;         // GPIO numbew fow WedPin[0]
  uint8_t      WedPin1;         // GPIO numbew fow WedPin[1]
  uint8_t      WedPin2;         // GPIO numbew fow WedPin[2]
  uint8_t      padding8_4;

  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadEnabwed;   // on ow off
  uint8_t      UcwkSpweadPewcent;   // Q4.4
  uint16_t     UcwkSpweadFweq;      // kHz

  // SOCCWK Spwead Spectwum
  uint8_t      SocwkSpweadEnabwed;   // on ow off
  uint8_t      SoccwkSpweadPewcent;   // Q4.4
  uint16_t     SoccwkSpweadFweq;      // kHz

  // Totaw boawd powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPadding;

  // Mvdd Svi2 Div Watio Setting
  uint32_t     MvddWatio; // This is used fow MVDD Vid wowkawound. It has 16 fwactionaw bits (Q16.16)

  // GPIO pins fow I2C communications with 2nd contwowwew fow Input Tewemetwy Sequence
  uint8_t      GpioI2cScw;          // Sewiaw Cwock
  uint8_t      GpioI2cSda;          // Sewiaw Data
  uint16_t     GpioPadding;

  // Additionaw WED Dispway Settings
  uint8_t      WedPin3;         // GPIO numbew fow WedPin[3] - PCIE GEN Speed
  uint8_t      WedPin4;         // GPIO numbew fow WedPin[4] - PMFW Ewwow Status
  uint16_t     WedEnabweMask;

  // Powew Wimit Scawaws
  uint8_t      PowewWimitScawaw[4];    //[PPT_THWOTTWEW_COUNT]

  uint8_t      MvddUwvPhaseSheddingMask;
  uint8_t      VddciUwvPhaseSheddingMask;
  uint8_t      Padding8_Psi1;
  uint8_t      Padding8_Psi2;

  uint32_t     BoawdWesewved[5];
};

stwuct smudpm_i2c_contwowwew_config_v3
{
  uint8_t   Enabwed;
  uint8_t   Speed;
  uint8_t   SwaveAddwess;
  uint8_t   ContwowwewPowt;
  uint8_t   ContwowwewName;
  uint8_t   ThewmawThwottew;
  uint8_t   I2cPwotocow;
  uint8_t   PaddingConfig;
};

stwuct atom_smc_dpm_info_v4_9
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;

  //SECTION: Gaming Cwocks
  //uint32_t     GamingCwk[6];

  // SECTION: I2C Contwow
  stwuct smudpm_i2c_contwowwew_config_v3  I2cContwowwews[16];     

  uint8_t      GpioScw;  // GPIO Numbew fow SCW Wine, used onwy fow CKSVII2C1
  uint8_t      GpioSda;  // GPIO Numbew fow SDA Wine, used onwy fow CKSVII2C1
  uint8_t      FchUsbPdSwaveAddw; //Fow wequesting USB PD contwowwew S-states via FCH I2C when entewing PME tuwn off
  uint8_t      I2cSpawe;

  // SECTION: SVI2 Boawd Pawametews
  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      VddciUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      MvddUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode

  // SECTION: Tewemetwy Settings
  uint16_t     GfxMaxCuwwent;   // in Amps
  uint8_t      GfxOffset;       // in Amps
  uint8_t      Padding_TewemetwyGfx;

  uint16_t     SocMaxCuwwent;   // in Amps
  uint8_t      SocOffset;       // in Amps
  uint8_t      Padding_TewemetwySoc;

  uint16_t     Mem0MaxCuwwent;   // in Amps
  uint8_t      Mem0Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem0;
  
  uint16_t     Mem1MaxCuwwent;   // in Amps
  uint8_t      Mem1Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem1;

  uint32_t     MvddWatio; // This is used fow MVDD  Svi2 Div Watio wowkawound. It has 16 fwactionaw bits (Q16.16)
  
  // SECTION: GPIO Settings
  uint8_t      AcDcGpio;        // GPIO pin configuwed fow AC/DC switching
  uint8_t      AcDcPowawity;    // GPIO powawity fow AC/DC switching
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event

  uint8_t      VW1HotGpio;      // GPIO pin configuwed fow VW1 HOT event 
  uint8_t      VW1HotPowawity;  // GPIO powawity fow VW1 HOT event 
  uint8_t      GthwGpio;        // GPIO pin configuwed fow GTHW Event
  uint8_t      GthwPowawity;    // wepwace GPIO powawity fow GTHW

  // WED Dispway Settings
  uint8_t      WedPin0;         // GPIO numbew fow WedPin[0]
  uint8_t      WedPin1;         // GPIO numbew fow WedPin[1]
  uint8_t      WedPin2;         // GPIO numbew fow WedPin[2]
  uint8_t      WedEnabweMask;

  uint8_t      WedPcie;        // GPIO numbew fow PCIE wesuwts
  uint8_t      WedEwwow;       // GPIO numbew fow Ewwow Cases
  uint8_t      WedSpawe1[2];

  // SECTION: Cwock Spwead Spectwum
  
  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz
  
  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadEnabwed;   // on ow off
  uint8_t      UcwkSpweadPewcent;   // Q4.4
  uint16_t     UcwkSpweadFweq;      // kHz

  // FCWK Spwead Spectwum
  uint8_t      FcwkSpweadEnabwed;   // on ow off
  uint8_t      FcwkSpweadPewcent;   // Q4.4
  uint16_t     FcwkSpweadFweq;      // kHz
  
  // Section: Memowy Config
  uint32_t     MemowyChannewEnabwed; // Fow DWAM use onwy, Max 32 channews enabwed bit mask. 
  
  uint8_t      DwamBitWidth; // Fow DWAM use onwy.  See Dwam Bit width type defines
  uint8_t      PaddingMem1[3];

  // Section: Totaw Boawd Powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPowewPadding; 
  
  // SECTION: XGMI Twaining
  uint8_t      XgmiWinkSpeed   [4];
  uint8_t      XgmiWinkWidth   [4];

  uint16_t     XgmiFcwkFweq    [4];
  uint16_t     XgmiSocVowtage  [4];

  // SECTION: Boawd Wesewved

  uint32_t     BoawdWesewved[16];

};

stwuct atom_smc_dpm_info_v4_10
{
  stwuct   atom_common_tabwe_headew  tabwe_headew;

  // SECTION: BOAWD PAWAMETEWS
  // Tewemetwy Settings
  uint16_t GfxMaxCuwwent; // in Amps
  uint8_t   GfxOffset;     // in Amps
  uint8_t  Padding_TewemetwyGfx;

  uint16_t SocMaxCuwwent; // in Amps
  uint8_t   SocOffset;     // in Amps
  uint8_t  Padding_TewemetwySoc;

  uint16_t MemMaxCuwwent; // in Amps
  uint8_t   MemOffset;     // in Amps
  uint8_t  Padding_TewemetwyMem;

  uint16_t BoawdMaxCuwwent; // in Amps
  uint8_t   BoawdOffset;     // in Amps
  uint8_t  Padding_TewemetwyBoawdInput;

  // Pwatfowm input tewemetwy vowtage coefficient
  uint32_t BoawdVowtageCoeffA; // decode by /1000
  uint32_t BoawdVowtageCoeffB; // decode by /1000

  // GPIO Settings
  uint8_t  VW0HotGpio;     // GPIO pin configuwed fow VW0 HOT event
  uint8_t  VW0HotPowawity; // GPIO powawity fow VW0 HOT event
  uint8_t  VW1HotGpio;     // GPIO pin configuwed fow VW1 HOT event
  uint8_t  VW1HotPowawity; // GPIO powawity fow VW1 HOT event

  // UCWK Spwead Spectwum
  uint8_t  UcwkSpweadEnabwed; // on ow off
  uint8_t  UcwkSpweadPewcent; // Q4.4
  uint16_t UcwkSpweadFweq;    // kHz

  // FCWK Spwead Spectwum
  uint8_t  FcwkSpweadEnabwed; // on ow off
  uint8_t  FcwkSpweadPewcent; // Q4.4
  uint16_t FcwkSpweadFweq;    // kHz

  // I2C Contwowwew Stwuctuwe
  stwuct smudpm_i2c_contwowwew_config_v3  I2cContwowwews[8];

  // GPIO pins fow I2C communications with 2nd contwowwew fow Input Tewemetwy Sequence
  uint8_t  GpioI2cScw; // Sewiaw Cwock
  uint8_t  GpioI2cSda; // Sewiaw Data
  uint16_t spawe5;

  uint32_t wesewved[16];
};

/* 
  ***************************************************************************
    Data Tabwe asic_pwofiwing_info  stwuctuwe
  ***************************************************************************
*/
stwuct  atom_asic_pwofiwing_info_v4_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t  maxvddc;                 
  uint32_t  minvddc;               
  uint32_t  avfs_meannsigma_acontant0;
  uint32_t  avfs_meannsigma_acontant1;
  uint32_t  avfs_meannsigma_acontant2;
  uint16_t  avfs_meannsigma_dc_tow_sigma;
  uint16_t  avfs_meannsigma_pwatfowm_mean;
  uint16_t  avfs_meannsigma_pwatfowm_sigma;
  uint32_t  gb_vdwoop_tabwe_cksoff_a0;
  uint32_t  gb_vdwoop_tabwe_cksoff_a1;
  uint32_t  gb_vdwoop_tabwe_cksoff_a2;
  uint32_t  gb_vdwoop_tabwe_ckson_a0;
  uint32_t  gb_vdwoop_tabwe_ckson_a1;
  uint32_t  gb_vdwoop_tabwe_ckson_a2;
  uint32_t  avfsgb_fuse_tabwe_cksoff_m1;
  uint32_t  avfsgb_fuse_tabwe_cksoff_m2;
  uint32_t  avfsgb_fuse_tabwe_cksoff_b;
  uint32_t  avfsgb_fuse_tabwe_ckson_m1;	
  uint32_t  avfsgb_fuse_tabwe_ckson_m2;
  uint32_t  avfsgb_fuse_tabwe_ckson_b;
  uint16_t  max_vowtage_0_25mv;
  uint8_t   enabwe_gb_vdwoop_tabwe_cksoff;
  uint8_t   enabwe_gb_vdwoop_tabwe_ckson;
  uint8_t   enabwe_gb_fuse_tabwe_cksoff;
  uint8_t   enabwe_gb_fuse_tabwe_ckson;
  uint16_t  psm_age_comfactow;
  uint8_t   enabwe_appwy_avfs_cksoff_vowtage;
  uint8_t   wesewved;
  uint32_t  dispcwk2gfxcwk_a;
  uint32_t  dispcwk2gfxcwk_b;
  uint32_t  dispcwk2gfxcwk_c;
  uint32_t  pixcwk2gfxcwk_a;
  uint32_t  pixcwk2gfxcwk_b;
  uint32_t  pixcwk2gfxcwk_c;
  uint32_t  dcefcwk2gfxcwk_a;
  uint32_t  dcefcwk2gfxcwk_b;
  uint32_t  dcefcwk2gfxcwk_c;
  uint32_t  phycwk2gfxcwk_a;
  uint32_t  phycwk2gfxcwk_b;
  uint32_t  phycwk2gfxcwk_c;
};

stwuct  atom_asic_pwofiwing_info_v4_2 {
	stwuct  atom_common_tabwe_headew  tabwe_headew;
	uint32_t  maxvddc;
	uint32_t  minvddc;
	uint32_t  avfs_meannsigma_acontant0;
	uint32_t  avfs_meannsigma_acontant1;
	uint32_t  avfs_meannsigma_acontant2;
	uint16_t  avfs_meannsigma_dc_tow_sigma;
	uint16_t  avfs_meannsigma_pwatfowm_mean;
	uint16_t  avfs_meannsigma_pwatfowm_sigma;
	uint32_t  gb_vdwoop_tabwe_cksoff_a0;
	uint32_t  gb_vdwoop_tabwe_cksoff_a1;
	uint32_t  gb_vdwoop_tabwe_cksoff_a2;
	uint32_t  gb_vdwoop_tabwe_ckson_a0;
	uint32_t  gb_vdwoop_tabwe_ckson_a1;
	uint32_t  gb_vdwoop_tabwe_ckson_a2;
	uint32_t  avfsgb_fuse_tabwe_cksoff_m1;
	uint32_t  avfsgb_fuse_tabwe_cksoff_m2;
	uint32_t  avfsgb_fuse_tabwe_cksoff_b;
	uint32_t  avfsgb_fuse_tabwe_ckson_m1;
	uint32_t  avfsgb_fuse_tabwe_ckson_m2;
	uint32_t  avfsgb_fuse_tabwe_ckson_b;
	uint16_t  max_vowtage_0_25mv;
	uint8_t   enabwe_gb_vdwoop_tabwe_cksoff;
	uint8_t   enabwe_gb_vdwoop_tabwe_ckson;
	uint8_t   enabwe_gb_fuse_tabwe_cksoff;
	uint8_t   enabwe_gb_fuse_tabwe_ckson;
	uint16_t  psm_age_comfactow;
	uint8_t   enabwe_appwy_avfs_cksoff_vowtage;
	uint8_t   wesewved;
	uint32_t  dispcwk2gfxcwk_a;
	uint32_t  dispcwk2gfxcwk_b;
	uint32_t  dispcwk2gfxcwk_c;
	uint32_t  pixcwk2gfxcwk_a;
	uint32_t  pixcwk2gfxcwk_b;
	uint32_t  pixcwk2gfxcwk_c;
	uint32_t  dcefcwk2gfxcwk_a;
	uint32_t  dcefcwk2gfxcwk_b;
	uint32_t  dcefcwk2gfxcwk_c;
	uint32_t  phycwk2gfxcwk_a;
	uint32_t  phycwk2gfxcwk_b;
	uint32_t  phycwk2gfxcwk_c;
	uint32_t  acg_gb_vdwoop_tabwe_a0;
	uint32_t  acg_gb_vdwoop_tabwe_a1;
	uint32_t  acg_gb_vdwoop_tabwe_a2;
	uint32_t  acg_avfsgb_fuse_tabwe_m1;
	uint32_t  acg_avfsgb_fuse_tabwe_m2;
	uint32_t  acg_avfsgb_fuse_tabwe_b;
	uint8_t   enabwe_acg_gb_vdwoop_tabwe;
	uint8_t   enabwe_acg_gb_fuse_tabwe;
	uint32_t  acg_dispcwk2gfxcwk_a;
	uint32_t  acg_dispcwk2gfxcwk_b;
	uint32_t  acg_dispcwk2gfxcwk_c;
	uint32_t  acg_pixcwk2gfxcwk_a;
	uint32_t  acg_pixcwk2gfxcwk_b;
	uint32_t  acg_pixcwk2gfxcwk_c;
	uint32_t  acg_dcefcwk2gfxcwk_a;
	uint32_t  acg_dcefcwk2gfxcwk_b;
	uint32_t  acg_dcefcwk2gfxcwk_c;
	uint32_t  acg_phycwk2gfxcwk_a;
	uint32_t  acg_phycwk2gfxcwk_b;
	uint32_t  acg_phycwk2gfxcwk_c;
};

/* 
  ***************************************************************************
    Data Tabwe muwtimedia_info  stwuctuwe
  ***************************************************************************
*/
stwuct atom_muwtimedia_info_v2_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint8_t uvdip_min_vew;
  uint8_t uvdip_max_vew;
  uint8_t vceip_min_vew;
  uint8_t vceip_max_vew;
  uint16_t uvd_enc_max_input_width_pixews;
  uint16_t uvd_enc_max_input_height_pixews;
  uint16_t vce_enc_max_input_width_pixews;
  uint16_t vce_enc_max_input_height_pixews; 
  uint32_t uvd_enc_max_bandwidth;           // 16x16 pixews/sec, codec independent
  uint32_t vce_enc_max_bandwidth;           // 16x16 pixews/sec, codec independent
};


/* 
  ***************************************************************************
    Data Tabwe umc_info  stwuctuwe
  ***************************************************************************
*/
stwuct atom_umc_info_v3_1
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t ucode_vewsion;
  uint32_t ucode_wom_stawtaddw;
  uint32_t ucode_wength;
  uint16_t umc_weg_init_offset;
  uint16_t customew_ucode_name_offset;
  uint16_t mcwk_ss_pewcentage;
  uint16_t mcwk_ss_wate_10hz;
  uint8_t umcip_min_vew;
  uint8_t umcip_max_vew;
  uint8_t vwam_type;              //enum of atom_dgpu_vwam_type
  uint8_t umc_config;
  uint32_t mem_wefcwk_10khz;
};

// umc_info.umc_config
enum atom_umc_config_def {
  UMC_CONFIG__ENABWE_1KB_INTEWWEAVE_MODE  =   0x00000001,
  UMC_CONFIG__DEFAUWT_MEM_ECC_ENABWE      =   0x00000002,
  UMC_CONFIG__ENABWE_HBM_WANE_WEPAIW      =   0x00000004,
  UMC_CONFIG__ENABWE_BANK_HAWVESTING      =   0x00000008,
  UMC_CONFIG__ENABWE_PHY_WEINIT           =   0x00000010,
  UMC_CONFIG__DISABWE_UCODE_CHKSTATUS     =   0x00000020,
};

stwuct atom_umc_info_v3_2
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t ucode_vewsion;
  uint32_t ucode_wom_stawtaddw;
  uint32_t ucode_wength;
  uint16_t umc_weg_init_offset;
  uint16_t customew_ucode_name_offset;
  uint16_t mcwk_ss_pewcentage;
  uint16_t mcwk_ss_wate_10hz;
  uint8_t umcip_min_vew;
  uint8_t umcip_max_vew;
  uint8_t vwam_type;              //enum of atom_dgpu_vwam_type
  uint8_t umc_config;
  uint32_t mem_wefcwk_10khz;
  uint32_t pstate_ucwk_10khz[4];
  uint16_t umcgowdenoffset;
  uint16_t densitygowdenoffset;
};

stwuct atom_umc_info_v3_3
{
  stwuct  atom_common_tabwe_headew  tabwe_headew;
  uint32_t ucode_wesewved;
  uint32_t ucode_wom_stawtaddw;
  uint32_t ucode_wength;
  uint16_t umc_weg_init_offset;
  uint16_t customew_ucode_name_offset;
  uint16_t mcwk_ss_pewcentage;
  uint16_t mcwk_ss_wate_10hz;
  uint8_t umcip_min_vew;
  uint8_t umcip_max_vew;
  uint8_t vwam_type;              //enum of atom_dgpu_vwam_type
  uint8_t umc_config;
  uint32_t mem_wefcwk_10khz;
  uint32_t pstate_ucwk_10khz[4];
  uint16_t umcgowdenoffset;
  uint16_t densitygowdenoffset;
  uint32_t umc_config1;
  uint32_t bist_data_stawtaddw;
  uint32_t wesewved[2];
};

enum atom_umc_config1_def {
	UMC_CONFIG1__ENABWE_PSTATE_PHASE_STOWE_TWAIN = 0x00000001,
	UMC_CONFIG1__ENABWE_AUTO_FWAMING = 0x00000002,
	UMC_CONFIG1__ENABWE_WESTOWE_BIST_DATA = 0x00000004,
	UMC_CONFIG1__DISABWE_STWOBE_MODE = 0x00000008,
	UMC_CONFIG1__DEBUG_DATA_PAWITY_EN = 0x00000010,
	UMC_CONFIG1__ENABWE_ECC_CAPABWE = 0x00010000,
};

stwuct atom_umc_info_v4_0 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint32_t ucode_wesewved[5];
	uint8_t umcip_min_vew;
	uint8_t umcip_max_vew;
	uint8_t vwam_type;
	uint8_t umc_config;
	uint32_t mem_wefcwk_10khz;
	uint32_t cwk_wesewved[4];
	uint32_t gowden_wesewved;
	uint32_t umc_config1;
	uint32_t wesewved[2];
	uint8_t channew_num;
	uint8_t channew_width;
	uint8_t channew_wesewve[2];
	uint8_t umc_info_wesewved[16];
};

/* 
  ***************************************************************************
    Data Tabwe vwam_info  stwuctuwe
  ***************************************************************************
*/
stwuct atom_vwam_moduwe_v9 {
  // Design Specific Vawues
  uint32_t  memowy_size;                   // Totaw memowy size in unit of MB fow CONFIG_MEMSIZE zewos
  uint32_t  channew_enabwe;                // bit vectow, each bit indicate specific channew enabwe ow not
  uint32_t  max_mem_cwk;                   // max memowy cwock of this memowy in unit of 10kHz, =0 means it is not defined
  uint16_t  wesewved[3];
  uint16_t  mem_vowtage;                   // mem_vowtage
  uint16_t  vwam_moduwe_size;              // Size of atom_vwam_moduwe_v9
  uint8_t   ext_memowy_id;                 // Cuwwent memowy moduwe ID
  uint8_t   memowy_type;                   // enum of atom_dgpu_vwam_type
  uint8_t   channew_num;                   // Numbew of mem. channews suppowted in this moduwe
  uint8_t   channew_width;                 // CHANNEW_16BIT/CHANNEW_32BIT/CHANNEW_64BIT
  uint8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uint8_t   tunningset_id;                 // MC phy wegistews set pew. 
  uint8_t   vendew_wev_id;                 // [7:4] Wevision, [3:0] Vendow code
  uint8_t   wefweshwate;                   // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uint8_t   hbm_ven_wev_id;		   // hbm_ven_wev_id
  uint8_t   vwam_wsd2;			   // wesewved
  chaw    dwam_pnstwing[20];               // pawt numbew end with '0'. 
};

stwuct atom_vwam_info_headew_v2_3 {
  stwuct   atom_common_tabwe_headew tabwe_headew;
  uint16_t mem_adjust_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow memowy vendow specific UMC adjust setting
  uint16_t mem_cwk_patch_tbwoffset;                      // offset of atom_umc_init_weg_bwock stwuctuwe fow memowy cwock specific UMC setting
  uint16_t mc_adjust_pewtiwe_tbwoffset;                  // offset of atom_umc_init_weg_bwock stwuctuwe fow Pew Byte Offset Pweset Settings
  uint16_t mc_phyinit_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init set
  uint16_t dwam_data_wemap_tbwoffset;                    // wesewved fow now
  uint16_t tmws_seq_offset;                              // offset of HBM tmws
  uint16_t post_ucode_init_offset;                       // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init aftew MC uCode compwete umc init
  uint16_t vwam_wsd2;
  uint8_t  vwam_moduwe_num;                              // indicate numbew of VWAM moduwe
  uint8_t  umcip_min_vew;
  uint8_t  umcip_max_vew;
  uint8_t  mc_phy_tiwe_num;                              // indicate the MCD tiwe numbew which use in DwamDataWemapTbw and usMcAdjustPewTiweTbwOffset
  stwuct   atom_vwam_moduwe_v9  vwam_moduwe[16];         // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
};

/*
  ***************************************************************************
    Data Tabwe vwam_info v3.0  stwuctuwe
  ***************************************************************************
*/
stwuct atom_vwam_moduwe_v3_0 {
	uint8_t density;
	uint8_t tunningset_id;
	uint8_t ext_memowy_id;
	uint8_t dwam_vendow_id;
	uint16_t dwam_info_offset;
	uint16_t mem_tuning_offset;
	uint16_t tmws_seq_offset;
	uint16_t wesewved1;
	uint32_t dwam_size_pew_ch;
	uint32_t wesewved[3];
	chaw dwam_pnstwing[40];
};

stwuct atom_vwam_info_headew_v3_0 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint16_t mem_tuning_tabwe_offset;
	uint16_t dwam_info_tabwe_offset;
	uint16_t tmws_tabwe_offset;
	uint16_t mc_init_tabwe_offset;
	uint16_t dwam_data_wemap_tabwe_offset;
	uint16_t umc_emuinittabwe_offset;
	uint16_t wesewved_sub_tabwe_offset[2];
	uint8_t vwam_moduwe_num;
	uint8_t umcip_min_vew;
	uint8_t umcip_max_vew;
	uint8_t mc_phy_tiwe_num;
	uint8_t memowy_type;
	uint8_t channew_num;
	uint8_t channew_width;
	uint8_t wesewved1;
	uint32_t channew_enabwe;
	uint32_t channew1_enabwe;
	uint32_t featuwe_enabwe;
	uint32_t featuwe1_enabwe;
	uint32_t hawdcode_mem_size;
	uint32_t wesewved4[4];
	stwuct atom_vwam_moduwe_v3_0 vwam_moduwe[8];
};

stwuct atom_umc_wegistew_addw_info{
  uint32_t  umc_wegistew_addw:24;
  uint32_t  umc_weg_type_ind:1;
  uint32_t  umc_weg_wsvd:7;
};

//atom_umc_wegistew_addw_info.
enum atom_umc_wegistew_addw_info_fwag{
  b3ATOM_UMC_WEG_ADD_INFO_INDIWECT_ACCESS  =0x01,
};

union atom_umc_wegistew_addw_info_access
{
  stwuct atom_umc_wegistew_addw_info umc_weg_addw;
  uint32_t u32umc_weg_addw;
};

stwuct atom_umc_weg_setting_id_config{
  uint32_t memcwockwange:24;
  uint32_t mem_bwk_id:8;
};

union atom_umc_weg_setting_id_config_access
{
  stwuct atom_umc_weg_setting_id_config umc_id_access;
  uint32_t  u32umc_id_access;
};

stwuct atom_umc_weg_setting_data_bwock{
  union atom_umc_weg_setting_id_config_access  bwock_id;
  uint32_t u32umc_weg_data[1];                       
};

stwuct atom_umc_init_weg_bwock{
  uint16_t umc_weg_num;
  uint16_t wesewved;    
  union atom_umc_wegistew_addw_info_access umc_weg_wist[1];     //fow awwocation puwpose, the weaw numbew come fwom umc_weg_num;
  stwuct atom_umc_weg_setting_data_bwock umc_weg_setting_wist[1];
};

stwuct atom_vwam_moduwe_v10 {
  // Design Specific Vawues
  uint32_t  memowy_size;                   // Totaw memowy size in unit of MB fow CONFIG_MEMSIZE zewos
  uint32_t  channew_enabwe;                // bit vectow, each bit indicate specific channew enabwe ow not
  uint32_t  max_mem_cwk;                   // max memowy cwock of this memowy in unit of 10kHz, =0 means it is not defined
  uint16_t  wesewved[3];
  uint16_t  mem_vowtage;                   // mem_vowtage
  uint16_t  vwam_moduwe_size;              // Size of atom_vwam_moduwe_v9
  uint8_t   ext_memowy_id;                 // Cuwwent memowy moduwe ID
  uint8_t   memowy_type;                   // enum of atom_dgpu_vwam_type
  uint8_t   channew_num;                   // Numbew of mem. channews suppowted in this moduwe
  uint8_t   channew_width;                 // CHANNEW_16BIT/CHANNEW_32BIT/CHANNEW_64BIT
  uint8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uint8_t   tunningset_id;                 // MC phy wegistews set pew
  uint8_t   vendew_wev_id;                 // [7:4] Wevision, [3:0] Vendow code
  uint8_t   wefweshwate;                   // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uint8_t   vwam_fwags;			   // bit0= bankgwoup enabwe
  uint8_t   vwam_wsd2;			   // wesewved
  uint16_t  gddw6_mw10;                    // gddw6 mode wegistew10 vawue
  uint16_t  gddw6_mw1;                     // gddw6 mode wegistew1 vawue
  uint16_t  gddw6_mw2;                     // gddw6 mode wegistew2 vawue
  uint16_t  gddw6_mw7;                     // gddw6 mode wegistew7 vawue
  chaw    dwam_pnstwing[20];               // pawt numbew end with '0'
};

stwuct atom_vwam_info_headew_v2_4 {
  stwuct   atom_common_tabwe_headew tabwe_headew;
  uint16_t mem_adjust_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow memowy vendow specific UMC adjust setting
  uint16_t mem_cwk_patch_tbwoffset;                      // offset of atom_umc_init_weg_bwock stwuctuwe fow memowy cwock specific UMC setting
  uint16_t mc_adjust_pewtiwe_tbwoffset;                  // offset of atom_umc_init_weg_bwock stwuctuwe fow Pew Byte Offset Pweset Settings
  uint16_t mc_phyinit_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init set
  uint16_t dwam_data_wemap_tbwoffset;                    // wesewved fow now
  uint16_t wesewved;                                     // offset of wesewved
  uint16_t post_ucode_init_offset;                       // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init aftew MC uCode compwete umc init
  uint16_t vwam_wsd2;
  uint8_t  vwam_moduwe_num;                              // indicate numbew of VWAM moduwe
  uint8_t  umcip_min_vew;
  uint8_t  umcip_max_vew;
  uint8_t  mc_phy_tiwe_num;                              // indicate the MCD tiwe numbew which use in DwamDataWemapTbw and usMcAdjustPewTiweTbwOffset
  stwuct   atom_vwam_moduwe_v10  vwam_moduwe[16];        // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
};

stwuct atom_vwam_moduwe_v11 {
	// Design Specific Vawues
	uint32_t  memowy_size;                   // Totaw memowy size in unit of MB fow CONFIG_MEMSIZE zewos
	uint32_t  channew_enabwe;                // bit vectow, each bit indicate specific channew enabwe ow not
	uint16_t  mem_vowtage;                   // mem_vowtage
	uint16_t  vwam_moduwe_size;              // Size of atom_vwam_moduwe_v9
	uint8_t   ext_memowy_id;                 // Cuwwent memowy moduwe ID
	uint8_t   memowy_type;                   // enum of atom_dgpu_vwam_type
	uint8_t   channew_num;                   // Numbew of mem. channews suppowted in this moduwe
	uint8_t   channew_width;                 // CHANNEW_16BIT/CHANNEW_32BIT/CHANNEW_64BIT
	uint8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
	uint8_t   tunningset_id;                 // MC phy wegistews set pew.
	uint16_t  wesewved[4];                   // wesewved
	uint8_t   vendew_wev_id;                 // [7:4] Wevision, [3:0] Vendow code
	uint8_t   wefweshwate;			 // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t   vwam_fwags;			 // bit0= bankgwoup enabwe
	uint8_t   vwam_wsd2;			 // wesewved
	uint16_t  gddw6_mw10;                    // gddw6 mode wegistew10 vawue
	uint16_t  gddw6_mw0;                     // gddw6 mode wegistew0 vawue
	uint16_t  gddw6_mw1;                     // gddw6 mode wegistew1 vawue
	uint16_t  gddw6_mw2;                     // gddw6 mode wegistew2 vawue
	uint16_t  gddw6_mw4;                     // gddw6 mode wegistew4 vawue
	uint16_t  gddw6_mw7;                     // gddw6 mode wegistew7 vawue
	uint16_t  gddw6_mw8;                     // gddw6 mode wegistew8 vawue
	chaw    dwam_pnstwing[40];               // pawt numbew end with '0'.
};

stwuct atom_gddw6_ac_timing_v2_5 {
	uint32_t  u32umc_id_access;
	uint8_t  WW;
	uint8_t  WW;
	uint8_t  tWAS;
	uint8_t  tWC;

	uint16_t  tWEFI;
	uint8_t  tWFC;
	uint8_t  tWFCpb;

	uint8_t  tWWEFD;
	uint8_t  tWCDWD;
	uint8_t  tWCDWW;
	uint8_t  tWP;

	uint8_t  tWWDS;
	uint8_t  tWWDW;
	uint8_t  tWW;
	uint8_t  tWTWS;

	uint8_t  tWTWW;
	uint8_t  tFAW;
	uint8_t  tCCDS;
	uint8_t  tCCDW;

	uint8_t  tCWCWW;
	uint8_t  tCWCWW;
	uint8_t  tCKE;
	uint8_t  tCKSWE;

	uint8_t  tCKSWX;
	uint8_t  tWTPS;
	uint8_t  tWTPW;
	uint8_t  tMWD;

	uint8_t  tMOD;
	uint8_t  tXS;
	uint8_t  tXHP;
	uint8_t  tXSMWS;

	uint32_t  tXSH;

	uint8_t  tPD;
	uint8_t  tXP;
	uint8_t  tCPDED;
	uint8_t  tACTPDE;

	uint8_t  tPWEPDE;
	uint8_t  tWEFPDE;
	uint8_t  tMWSPDEN;
	uint8_t  tWDSWE;

	uint8_t  tWWSWE;
	uint8_t  tPPD;
	uint8_t  tCCDMW;
	uint8_t  tWTWTW;

	uint8_t  tWTWTW;
	uint8_t  tWEFTW;
	uint8_t  VNDW;
	uint8_t  wesewved[9];
};

stwuct atom_gddw6_bit_byte_wemap {
	uint32_t dphy_bytewemap;    //mmUMC_DPHY_ByteWemap
	uint32_t dphy_bitwemap0;    //mmUMC_DPHY_BitWemap0
	uint32_t dphy_bitwemap1;    //mmUMC_DPHY_BitWemap1
	uint32_t dphy_bitwemap2;    //mmUMC_DPHY_BitWemap2
	uint32_t aphy_bitwemap0;    //mmUMC_APHY_BitWemap0
	uint32_t aphy_bitwemap1;    //mmUMC_APHY_BitWemap1
	uint32_t phy_dwam;          //mmUMC_PHY_DWAM
};

stwuct atom_gddw6_dwam_data_wemap {
	uint32_t tabwe_size;
	uint8_t phyintf_ck_invewted[8];     //UMC_PHY_PHYINTF_CNTW.INV_CK
	stwuct atom_gddw6_bit_byte_wemap bit_byte_wemap[16];
};

stwuct atom_vwam_info_headew_v2_5 {
	stwuct   atom_common_tabwe_headew tabwe_headew;
	uint16_t mem_adjust_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow memowy vendow specific UMC adjust settings
	uint16_t gddw6_ac_timing_offset;                     // offset of atom_gddw6_ac_timing_v2_5 stwuctuwe fow memowy cwock specific UMC settings
	uint16_t mc_adjust_pewtiwe_tbwoffset;                  // offset of atom_umc_init_weg_bwock stwuctuwe fow Pew Byte Offset Pweset Settings
	uint16_t mc_phyinit_tbwoffset;                         // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init set
	uint16_t dwam_data_wemap_tbwoffset;                    // offset of atom_gddw6_dwam_data_wemap awway to indicate DWAM data wane to GPU mapping
	uint16_t wesewved;                                     // offset of wesewved
	uint16_t post_ucode_init_offset;                       // offset of atom_umc_init_weg_bwock stwuctuwe fow MC phy init aftew MC uCode compwete umc init
	uint16_t stwobe_mode_patch_tbwoffset;                  // offset of atom_umc_init_weg_bwock stwuctuwe fow Stwobe Mode memowy cwock specific UMC settings
	uint8_t  vwam_moduwe_num;                              // indicate numbew of VWAM moduwe
	uint8_t  umcip_min_vew;
	uint8_t  umcip_max_vew;
	uint8_t  mc_phy_tiwe_num;                              // indicate the MCD tiwe numbew which use in DwamDataWemapTbw and usMcAdjustPewTiweTbwOffset
	stwuct   atom_vwam_moduwe_v11  vwam_moduwe[16];        // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
};

stwuct atom_vwam_info_headew_v2_6 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	uint16_t mem_adjust_tbwoffset;
	uint16_t mem_cwk_patch_tbwoffset;
	uint16_t mc_adjust_pewtiwe_tbwoffset;
	uint16_t mc_phyinit_tbwoffset;
	uint16_t dwam_data_wemap_tbwoffset;
	uint16_t tmws_seq_offset;
	uint16_t post_ucode_init_offset;
	uint16_t vwam_wsd2;
	uint8_t  vwam_moduwe_num;
	uint8_t  umcip_min_vew;
	uint8_t  umcip_max_vew;
	uint8_t  mc_phy_tiwe_num;
	stwuct atom_vwam_moduwe_v9 vwam_moduwe[16];
};
/* 
  ***************************************************************************
    Data Tabwe vowtageobject_info  stwuctuwe
  ***************************************************************************
*/
stwuct  atom_i2c_data_entwy
{
  uint16_t  i2c_weg_index;               // i2c wegistew addwess, can be up to 16bit
  uint16_t  i2c_weg_data;                // i2c wegistew data, can be up to 16bit
};

stwuct atom_vowtage_object_headew_v4{
  uint8_t    vowtage_type;                           //enum atom_vowtage_type
  uint8_t    vowtage_mode;                           //enum atom_vowtage_object_mode 
  uint16_t   object_size;                            //Size of Object
};

// atom_vowtage_object_headew_v4.vowtage_mode
enum atom_vowtage_object_mode 
{
   VOWTAGE_OBJ_GPIO_WUT              =  0,        //VOWTAGE and GPIO Wookup tabwe ->atom_gpio_vowtage_object_v4
   VOWTAGE_OBJ_VW_I2C_INIT_SEQ       =  3,        //VOWTAGE WEGUWATOW INIT sequece thwough I2C -> atom_i2c_vowtage_object_v4
   VOWTAGE_OBJ_PHASE_WUT             =  4,        //Set Vweguwatow Phase wookup tabwe ->atom_gpio_vowtage_object_v4
   VOWTAGE_OBJ_SVID2                 =  7,        //Indicate vowtage contwow by SVID2 ->atom_svid2_vowtage_object_v4
   VOWTAGE_OBJ_EVV                   =  8, 
   VOWTAGE_OBJ_MEWGED_POWEW          =  9,
};

stwuct  atom_i2c_vowtage_object_v4
{
   stwuct atom_vowtage_object_headew_v4 headew;  // vowtage mode = VOWTAGE_OBJ_VW_I2C_INIT_SEQ
   uint8_t  weguwatow_id;                        //Indicate Vowtage Weguwatow Id
   uint8_t  i2c_id;
   uint8_t  i2c_swave_addw;
   uint8_t  i2c_contwow_offset;       
   uint8_t  i2c_fwag;                            // Bit0: 0 - One byte data; 1 - Two byte data
   uint8_t  i2c_speed;                           // =0, use defauwt i2c speed, othewwise use it in unit of kHz. 
   uint8_t  wesewved[2];
   stwuct atom_i2c_data_entwy i2cdatawut[1];     // end with 0xff
};

// ATOM_I2C_VOWTAGE_OBJECT_V3.ucVowtageContwowFwag
enum atom_i2c_vowtage_contwow_fwag
{
   VOWTAGE_DATA_ONE_BYTE = 0,
   VOWTAGE_DATA_TWO_BYTE = 1,
};


stwuct atom_vowtage_gpio_map_wut
{
  uint32_t  vowtage_gpio_weg_vaw;              // The Vowtage ID which is used to pwogwam GPIO wegistew
  uint16_t  vowtage_wevew_mv;                  // The cowwesponding Vowtage Vawue, in mV
};

stwuct atom_gpio_vowtage_object_v4
{
   stwuct atom_vowtage_object_headew_v4 headew;  // vowtage mode = VOWTAGE_OBJ_GPIO_WUT ow VOWTAGE_OBJ_PHASE_WUT
   uint8_t  gpio_contwow_id;                     // defauwt is 0 which indicate contwow thwough CG VID mode 
   uint8_t  gpio_entwy_num;                      // indiate the entwy numbews of Votwage/Gpio vawue Wook up tabwe
   uint8_t  phase_deway_us;                      // phase deway in unit of micwo second
   uint8_t  wesewved;   
   uint32_t gpio_mask_vaw;                         // GPIO Mask vawue
   stwuct atom_vowtage_gpio_map_wut vowtage_gpio_wut[1];
};

stwuct  atom_svid2_vowtage_object_v4
{
   stwuct atom_vowtage_object_headew_v4 headew;  // vowtage mode = VOWTAGE_OBJ_SVID2
   uint8_t woadwine_psi1;                        // bit4:0= woadwine setting ( Cowe Woadwine twim and offset twim ), bit5=0:PSI1_W disabwe =1: PSI1_W enabwe
   uint8_t psi0_w_vid_thwesd;                    // VW PSI0_W VID thweshowd
   uint8_t psi0_enabwe;                          // 
   uint8_t maxvstep;
   uint8_t tewemetwy_offset;
   uint8_t tewemetwy_gain; 
   uint16_t wesewved1;
};

stwuct atom_mewged_vowtage_object_v4
{
  stwuct atom_vowtage_object_headew_v4 headew;  // vowtage mode = VOWTAGE_OBJ_MEWGED_POWEW
  uint8_t  mewged_powewwaiw_type;               //enum atom_vowtage_type
  uint8_t  wesewved[3];
};

union atom_vowtage_object_v4{
  stwuct atom_gpio_vowtage_object_v4 gpio_vowtage_obj;
  stwuct atom_i2c_vowtage_object_v4 i2c_vowtage_obj;
  stwuct atom_svid2_vowtage_object_v4 svid2_vowtage_obj;
  stwuct atom_mewged_vowtage_object_v4 mewged_vowtage_obj;
};

stwuct  atom_vowtage_objects_info_v4_1
{
  stwuct atom_common_tabwe_headew tabwe_headew; 
  union atom_vowtage_object_v4 vowtage_object[1];   //Info fow Vowtage contwow
};


/* 
  ***************************************************************************
              Aww Command Function stwuctuwe definition 
  *************************************************************************** 
*/   

/* 
  ***************************************************************************
              Stwuctuwes used by asic_init
  *************************************************************************** 
*/   

stwuct asic_init_engine_pawametews
{
  uint32_t scwkfweqin10khz:24;
  uint32_t enginefwag:8;              /* enum atom_asic_init_engine_fwag  */
};

stwuct asic_init_mem_pawametews
{
  uint32_t mcwkfweqin10khz:24;
  uint32_t memfwag:8;                 /* enum atom_asic_init_mem_fwag  */
};

stwuct asic_init_pawametews_v2_1
{
  stwuct asic_init_engine_pawametews enginepawam;
  stwuct asic_init_mem_pawametews mempawam;
};

stwuct asic_init_ps_awwocation_v2_1
{
  stwuct asic_init_pawametews_v2_1 pawam;
  uint32_t wesewved[16];
};


enum atom_asic_init_engine_fwag
{
  b3NOWMAW_ENGINE_INIT = 0,
  b3SWIOV_SKIP_ASIC_INIT = 0x02,
  b3SWIOV_WOAD_UCODE = 0x40,
};

enum atom_asic_init_mem_fwag
{
  b3NOWMAW_MEM_INIT = 0,
  b3DWAM_SEWF_WEFWESH_EXIT =0x20,
};

/* 
  ***************************************************************************
              Stwuctuwes used by setenginecwock
  *************************************************************************** 
*/   

stwuct set_engine_cwock_pawametews_v2_1
{
  uint32_t scwkfweqin10khz:24;
  uint32_t scwkfwag:8;              /* enum atom_set_engine_mem_cwock_fwag,  */
  uint32_t wesewved[10];
};

stwuct set_engine_cwock_ps_awwocation_v2_1
{
  stwuct set_engine_cwock_pawametews_v2_1 cwockinfo;
  uint32_t wesewved[10];
};


enum atom_set_engine_mem_cwock_fwag
{
  b3NOWMAW_CHANGE_CWOCK = 0,
  b3FIWST_TIME_CHANGE_CWOCK = 0x08,
  b3STOWE_DPM_TWAINGING = 0x40,         //Appwicabwe to memowy cwock change,when set, it stowe specific DPM mode twaining wesuwt
};

/* 
  ***************************************************************************
              Stwuctuwes used by getenginecwock
  *************************************************************************** 
*/   
stwuct get_engine_cwock_pawametew
{
  uint32_t scwk_10khz;          // cuwwent engine speed in 10KHz unit
  uint32_t wesewved;
};

/* 
  ***************************************************************************
              Stwuctuwes used by setmemowycwock
  *************************************************************************** 
*/   
stwuct set_memowy_cwock_pawametews_v2_1
{
  uint32_t mcwkfweqin10khz:24;
  uint32_t mcwkfwag:8;              /* enum atom_set_engine_mem_cwock_fwag,  */
  uint32_t wesewved[10];
};

stwuct set_memowy_cwock_ps_awwocation_v2_1
{
  stwuct set_memowy_cwock_pawametews_v2_1 cwockinfo;
  uint32_t wesewved[10];
};


/* 
  ***************************************************************************
              Stwuctuwes used by getmemowycwock
  *************************************************************************** 
*/   
stwuct get_memowy_cwock_pawametew
{
  uint32_t mcwk_10khz;          // cuwwent engine speed in 10KHz unit
  uint32_t wesewved;
};



/* 
  ***************************************************************************
              Stwuctuwes used by setvowtage
  *************************************************************************** 
*/   

stwuct set_vowtage_pawametews_v1_4
{
  uint8_t  vowtagetype;                /* enum atom_vowtage_type */
  uint8_t  command;                    /* Indicate action: Set vowtage wevew, enum atom_set_vowtage_command */
  uint16_t vwevew_mv;                  /* weaw vowtage wevew in unit of mv ow Vowtage Phase (0, 1, 2, .. ) */
};

//set_vowtage_pawametews_v2_1.vowtagemode
enum atom_set_vowtage_command{
  ATOM_SET_VOWTAGE  = 0,
  ATOM_INIT_VOWTAGE_WEGUWATOW = 3,
  ATOM_SET_VOWTAGE_PHASE = 4,
  ATOM_GET_WEAKAGE_ID    = 8,
};

stwuct set_vowtage_ps_awwocation_v1_4
{
  stwuct set_vowtage_pawametews_v1_4 setvowtagepawam;
  uint32_t wesewved[10];
};


/* 
  ***************************************************************************
              Stwuctuwes used by computegpucwockpawam
  *************************************************************************** 
*/   

//ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag
enum atom_gpu_cwock_type 
{
  COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK =0x00,
  COMPUTE_GPUCWK_INPUT_FWAG_GFXCWK =0x01,
  COMPUTE_GPUCWK_INPUT_FWAG_UCWK =0x02,
};

stwuct compute_gpu_cwock_input_pawametew_v1_8
{
  uint32_t  gpucwock_10khz:24;         //Input= tawget cwock, output = actuaw cwock 
  uint32_t  gpu_cwock_type:8;          //Input indicate cwock type: enum atom_gpu_cwock_type
  uint32_t  wesewved[5];
};


stwuct compute_gpu_cwock_output_pawametew_v1_8
{
  uint32_t  gpucwock_10khz:24;              //Input= tawget cwock, output = actuaw cwock 
  uint32_t  dfs_did:8;                      //wetuwn pawametew: DFS dividew which is used to pwogwam to wegistew diwectwy
  uint32_t  pww_fb_muwt;                    //Feedback Muwtipwiew, bit 8:0 int, bit 15:12 post_div, bit 31:16 fwac
  uint32_t  pww_ss_fbsmuwt;                 // Spwead FB Muwt: bit 8:0 int, bit 31:16 fwac
  uint16_t  pww_ss_swew_fwac;
  uint8_t   pww_ss_enabwe;
  uint8_t   wesewved;
  uint32_t  wesewved1[2];
};



/* 
  ***************************************************************************
              Stwuctuwes used by WeadEfuseVawue
  *************************************************************************** 
*/   

stwuct wead_efuse_input_pawametews_v3_1
{
  uint16_t efuse_stawt_index;
  uint8_t  wesewved;
  uint8_t  bitswen;
};

// WeadEfuseVawue input/output pawametew
union wead_efuse_vawue_pawametews_v3_1
{
  stwuct wead_efuse_input_pawametews_v3_1 efuse_info;
  uint32_t efusevawue;
};


/* 
  ***************************************************************************
              Stwuctuwes used by getsmucwockinfo
  *************************************************************************** 
*/   
stwuct atom_get_smu_cwock_info_pawametews_v3_1
{
  uint8_t syspww_id;          // 0= syspww0, 1=syspww1, 2=syspww2                
  uint8_t cwk_id;             // atom_smu9_syspww0_cwock_id  (onwy vawid when command == GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ )
  uint8_t command;            // enum of atom_get_smu_cwock_info_command
  uint8_t dfsdid;             // =0: get DFS DID fwom wegistew, >0, give DFS dividew, (onwy vawid when command == GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ )
};

enum atom_get_smu_cwock_info_command 
{
  GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ       = 0,
  GET_SMU_CWOCK_INFO_V3_1_GET_PWWVCO_FWEQ      = 1,
  GET_SMU_CWOCK_INFO_V3_1_GET_PWWWEFCWK_FWEQ   = 2,
};

enum atom_smu9_syspww0_cwock_id
{
  SMU9_SYSPWW0_SMNCWK_ID   = 0,       //  SMNCWK
  SMU9_SYSPWW0_SOCCWK_ID   = 1,       //	SOCCWK (FCWK)
  SMU9_SYSPWW0_MP0CWK_ID   = 2,       //	MP0CWK
  SMU9_SYSPWW0_MP1CWK_ID   = 3,       //	MP1CWK
  SMU9_SYSPWW0_WCWK_ID     = 4,       //	WCWK
  SMU9_SYSPWW0_DCWK_ID     = 5,       //	DCWK
  SMU9_SYSPWW0_VCWK_ID     = 6,       //	VCWK
  SMU9_SYSPWW0_ECWK_ID     = 7,       //	ECWK
  SMU9_SYSPWW0_DCEFCWK_ID  = 8,       //	DCEFCWK
  SMU9_SYSPWW0_DPWEFCWK_ID = 10,      //	DPWEFCWK
  SMU9_SYSPWW0_DISPCWK_ID  = 11,      //	DISPCWK
};

enum atom_smu11_syspww_id {
  SMU11_SYSPWW0_ID            = 0,
  SMU11_SYSPWW1_0_ID          = 1,
  SMU11_SYSPWW1_1_ID          = 2,
  SMU11_SYSPWW1_2_ID          = 3,
  SMU11_SYSPWW2_ID            = 4,
  SMU11_SYSPWW3_0_ID          = 5,
  SMU11_SYSPWW3_1_ID          = 6,
};

enum atom_smu11_syspww0_cwock_id {
  SMU11_SYSPWW0_ECWK_ID     = 0,       //	ECWK
  SMU11_SYSPWW0_SOCCWK_ID   = 1,       //	SOCCWK
  SMU11_SYSPWW0_MP0CWK_ID   = 2,       //	MP0CWK
  SMU11_SYSPWW0_DCWK_ID     = 3,       //	DCWK
  SMU11_SYSPWW0_VCWK_ID     = 4,       //	VCWK
  SMU11_SYSPWW0_DCEFCWK_ID  = 5,       //	DCEFCWK
};

enum atom_smu11_syspww1_0_cwock_id {
  SMU11_SYSPWW1_0_UCWKA_ID   = 0,       // UCWK_a
};

enum atom_smu11_syspww1_1_cwock_id {
  SMU11_SYSPWW1_0_UCWKB_ID   = 0,       // UCWK_b
};

enum atom_smu11_syspww1_2_cwock_id {
  SMU11_SYSPWW1_0_FCWK_ID   = 0,        // FCWK
};

enum atom_smu11_syspww2_cwock_id {
  SMU11_SYSPWW2_GFXCWK_ID   = 0,        // GFXCWK
};

enum atom_smu11_syspww3_0_cwock_id {
  SMU11_SYSPWW3_0_WAFCWK_ID = 0,       //	WAFCWK
  SMU11_SYSPWW3_0_DISPCWK_ID = 1,      //	DISPCWK
  SMU11_SYSPWW3_0_DPWEFCWK_ID = 2,     //	DPWEFCWK
};

enum atom_smu11_syspww3_1_cwock_id {
  SMU11_SYSPWW3_1_MP1CWK_ID = 0,       //	MP1CWK
  SMU11_SYSPWW3_1_SMNCWK_ID = 1,       //	SMNCWK
  SMU11_SYSPWW3_1_WCWK_ID = 2,         //	WCWK
};

enum atom_smu12_syspww_id {
  SMU12_SYSPWW0_ID          = 0,
  SMU12_SYSPWW1_ID          = 1,
  SMU12_SYSPWW2_ID          = 2,
  SMU12_SYSPWW3_0_ID        = 3,
  SMU12_SYSPWW3_1_ID        = 4,
};

enum atom_smu12_syspww0_cwock_id {
  SMU12_SYSPWW0_SMNCWK_ID   = 0,			//	SOCCWK
  SMU12_SYSPWW0_SOCCWK_ID   = 1,			//	SOCCWK
  SMU12_SYSPWW0_MP0CWK_ID   = 2,			//	MP0CWK
  SMU12_SYSPWW0_MP1CWK_ID   = 3,			//	MP1CWK
  SMU12_SYSPWW0_MP2CWK_ID   = 4,			//	MP2CWK
  SMU12_SYSPWW0_VCWK_ID     = 5,			//	VCWK
  SMU12_SYSPWW0_WCWK_ID     = 6,			//	WCWK
  SMU12_SYSPWW0_DCWK_ID     = 7,			//	DCWK
  SMU12_SYSPWW0_ACWK_ID     = 8,			//	ACWK
  SMU12_SYSPWW0_ISPCWK_ID   = 9,			//	ISPCWK
  SMU12_SYSPWW0_SHUBCWK_ID  = 10,			//	SHUBCWK
};

enum atom_smu12_syspww1_cwock_id {
  SMU12_SYSPWW1_DISPCWK_ID  = 0,      //	DISPCWK
  SMU12_SYSPWW1_DPPCWK_ID   = 1,      //	DPPCWK
  SMU12_SYSPWW1_DPWEFCWK_ID = 2,      //	DPWEFCWK
  SMU12_SYSPWW1_DCFCWK_ID   = 3,      //	DCFCWK
};

enum atom_smu12_syspww2_cwock_id {
  SMU12_SYSPWW2_Pwe_GFXCWK_ID = 0,   // Pwe_GFXCWK
};

enum atom_smu12_syspww3_0_cwock_id {
  SMU12_SYSPWW3_0_FCWK_ID = 0,      //	FCWK
};

enum atom_smu12_syspww3_1_cwock_id {
  SMU12_SYSPWW3_1_UMCCWK_ID = 0,    //	UMCCWK
};

stwuct  atom_get_smu_cwock_info_output_pawametews_v3_1
{
  union {
    uint32_t smu_cwock_fweq_hz;
    uint32_t syspwwvcofweq_10khz;
    uint32_t sysspwwwefcwk_10khz;
  }atom_smu_outputcwkfweq;
};



/* 
  ***************************************************************************
              Stwuctuwes used by dynamicmemowysettings
  *************************************************************************** 
*/   

enum atom_dynamic_memowy_setting_command 
{
  COMPUTE_MEMOWY_PWW_PAWAM = 1,
  COMPUTE_ENGINE_PWW_PAWAM = 2,
  ADJUST_MC_SETTING_PAWAM = 3,
};

/* when command = COMPUTE_MEMOWY_PWW_PAWAM ow ADJUST_MC_SETTING_PAWAM */
stwuct dynamic_mcwk_settings_pawametews_v2_1
{
  uint32_t  mcwk_10khz:24;         //Input= tawget mcwk
  uint32_t  command:8;             //command enum of atom_dynamic_memowy_setting_command
  uint32_t  wesewved;
};

/* when command = COMPUTE_ENGINE_PWW_PAWAM */
stwuct dynamic_scwk_settings_pawametews_v2_1
{
  uint32_t  scwk_10khz:24;         //Input= tawget mcwk
  uint32_t  command:8;             //command enum of atom_dynamic_memowy_setting_command
  uint32_t  mcwk_10khz;
  uint32_t  wesewved;
};

union dynamic_memowy_settings_pawametews_v2_1
{
  stwuct dynamic_mcwk_settings_pawametews_v2_1 mcwk_setting;
  stwuct dynamic_scwk_settings_pawametews_v2_1 scwk_setting;
};



/* 
  ***************************************************************************
              Stwuctuwes used by memowytwaining
  *************************************************************************** 
*/   

enum atom_umc6_0_ucode_function_caww_enum_id
{
  UMC60_UCODE_FUNC_ID_WEINIT                 = 0,
  UMC60_UCODE_FUNC_ID_ENTEW_SEWFWEFWESH      = 1,
  UMC60_UCODE_FUNC_ID_EXIT_SEWFWEFWESH       = 2,
};


stwuct memowy_twaining_pawametews_v2_1
{
  uint8_t ucode_func_id;
  uint8_t ucode_wesewved[3];
  uint32_t wesewved[5];
};


/* 
  ***************************************************************************
              Stwuctuwes used by setpixewcwock
  *************************************************************************** 
*/   

stwuct set_pixew_cwock_pawametew_v1_7
{
    uint32_t pixcwk_100hz;               // tawget the pixew cwock to dwive the CWTC timing in unit of 100Hz. 

    uint8_t  pww_id;                     // ATOM_PHY_PWW0/ATOM_PHY_PWW1/ATOM_PPWW0
    uint8_t  encodewobjid;               // ASIC encodew id defined in objectId.h, 
                                         // indicate which gwaphic encodew wiww be used. 
    uint8_t  encodew_mode;               // Encodew mode: 
    uint8_t  miscinfo;                   // enum atom_set_pixew_cwock_v1_7_misc_info
    uint8_t  cwtc_id;                    // enum of atom_cwtc_def
    uint8_t  deep_cowow_watio;           // HDMI panew bit depth: enum atom_set_pixew_cwock_v1_7_deepcowow_watio
    uint8_t  wesewved1[2];    
    uint32_t wesewved2;
};

//ucMiscInfo
enum atom_set_pixew_cwock_v1_7_misc_info
{
  PIXEW_CWOCK_V7_MISC_FOWCE_PWOG_PPWW         = 0x01,
  PIXEW_CWOCK_V7_MISC_PWOG_PHYPWW             = 0x02,
  PIXEW_CWOCK_V7_MISC_YUV420_MODE             = 0x04,
  PIXEW_CWOCK_V7_MISC_DVI_DUAWWINK_EN         = 0x08,
  PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC             = 0x30,
  PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_XTAWIN      = 0x00,
  PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_PCIE        = 0x10,
  PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_GENWK       = 0x20,
  PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_WEFPAD      = 0x30, 
  PIXEW_CWOCK_V7_MISC_ATOMIC_UPDATE           = 0x40,
  PIXEW_CWOCK_V7_MISC_FOWCE_SS_DIS            = 0x80,
};

/* deep_cowow_watio */
enum atom_set_pixew_cwock_v1_7_deepcowow_watio
{
  PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_DIS          = 0x00,      //00 - DCCG_DEEP_COWOW_DTO_DISABWE: Disabwe Deep Cowow DTO 
  PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_5_4          = 0x01,      //01 - DCCG_DEEP_COWOW_DTO_5_4_WATIO: Set Deep Cowow DTO to 5:4 
  PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_3_2          = 0x02,      //02 - DCCG_DEEP_COWOW_DTO_3_2_WATIO: Set Deep Cowow DTO to 3:2 
  PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_2_1          = 0x03,      //03 - DCCG_DEEP_COWOW_DTO_2_1_WATIO: Set Deep Cowow DTO to 2:1 
};

/* 
  ***************************************************************************
              Stwuctuwes used by setdcecwock
  *************************************************************************** 
*/   

// SetDCECwock input pawametew fow DCE11.2( EWM and BF ) and above 
stwuct set_dce_cwock_pawametews_v2_1
{
  uint32_t dcecwk_10khz;                               // tawget DCE fwequency in unit of 10KHZ, wetuwn weaw DISPCWK/DPWEFCWK fwequency. 
  uint8_t  dcecwktype;                                 // =0: DISPCWK  =1: DPWEFCWK  =2: PIXCWK
  uint8_t  dcecwkswc;                                  // ATOM_PWW0 ow ATOM_GCK_DFS ow ATOM_FCH_CWK ow ATOM_COMBOPHY_PWWx
  uint8_t  dcecwkfwag;                                 // Bit [1:0] = PPWW wef cwock souwce ( when ucDCECwkSwc= ATOM_PPWW0 )
  uint8_t  cwtc_id;                                    // ucDisp Pipe Id, ATOM_CWTC0/1/2/..., use onwy when ucDCECwkType = PIXCWK
};

//ucDCECwkType
enum atom_set_dce_cwock_cwock_type
{
  DCE_CWOCK_TYPE_DISPCWK                      = 0,
  DCE_CWOCK_TYPE_DPWEFCWK                     = 1,
  DCE_CWOCK_TYPE_PIXEWCWK                     = 2,        // used by VBIOS intewnawwy, cawwed by SetPixewCwock 
};

//ucDCECwkFwag when ucDCECwkType == DPWEFCWK 
enum atom_set_dce_cwock_dpwefcwk_fwag
{
  DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_MASK          = 0x03,
  DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENEWICA      = 0x00,
  DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENWK         = 0x01,
  DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_PCIE          = 0x02,
  DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_XTAWIN        = 0x03,
};

//ucDCECwkFwag when ucDCECwkType == PIXCWK 
enum atom_set_dce_cwock_pixcwk_fwag
{
  DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_MASK    = 0x03,
  DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_DIS     = 0x00,      //00 - DCCG_DEEP_COWOW_DTO_DISABWE: Disabwe Deep Cowow DTO 
  DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_5_4     = 0x01,      //01 - DCCG_DEEP_COWOW_DTO_5_4_WATIO: Set Deep Cowow DTO to 5:4 
  DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_3_2     = 0x02,      //02 - DCCG_DEEP_COWOW_DTO_3_2_WATIO: Set Deep Cowow DTO to 3:2 
  DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_2_1     = 0x03,      //03 - DCCG_DEEP_COWOW_DTO_2_1_WATIO: Set Deep Cowow DTO to 2:1 
  DCE_CWOCK_FWAG_PIXCWK_YUV420_MODE           = 0x04,
};

stwuct set_dce_cwock_ps_awwocation_v2_1
{
  stwuct set_dce_cwock_pawametews_v2_1 pawam;
  uint32_t uwWesewved[2];
};


/****************************************************************************/   
// Stwuctuwes used by BwankCWTC
/****************************************************************************/   
stwuct bwank_cwtc_pawametews
{
  uint8_t  cwtc_id;                   // enum atom_cwtc_def
  uint8_t  bwanking;                  // enum atom_bwank_cwtc_command
  uint16_t wesewved;
  uint32_t wesewved1;
};

enum atom_bwank_cwtc_command
{
  ATOM_BWANKING         = 1,
  ATOM_BWANKING_OFF     = 0,
};

/****************************************************************************/   
// Stwuctuwes used by enabwecwtc
/****************************************************************************/   
stwuct enabwe_cwtc_pawametews
{
  uint8_t cwtc_id;                    // enum atom_cwtc_def
  uint8_t enabwe;                     // ATOM_ENABWE ow ATOM_DISABWE 
  uint8_t padding[2];
};


/****************************************************************************/   
// Stwuctuwe used by EnabweDispPowewGating
/****************************************************************************/   
stwuct enabwe_disp_powew_gating_pawametews_v2_1
{
  uint8_t disp_pipe_id;                // ATOM_CWTC1, ATOM_CWTC2, ...
  uint8_t enabwe;                     // ATOM_ENABWE ow ATOM_DISABWE
  uint8_t padding[2];
};

stwuct enabwe_disp_powew_gating_ps_awwocation 
{
  stwuct enabwe_disp_powew_gating_pawametews_v2_1 pawam;
  uint32_t uwWesewved[4];
};

/****************************************************************************/   
// Stwuctuwe used in setcwtc_usingdtdtiming
/****************************************************************************/   
stwuct set_cwtc_using_dtd_timing_pawametews
{
  uint16_t  h_size;
  uint16_t  h_bwanking_time;
  uint16_t  v_size;
  uint16_t  v_bwanking_time;
  uint16_t  h_syncoffset;
  uint16_t  h_syncwidth;
  uint16_t  v_syncoffset;
  uint16_t  v_syncwidth;
  uint16_t  modemiscinfo;  
  uint8_t   h_bowdew;
  uint8_t   v_bowdew;
  uint8_t   cwtc_id;                   // enum atom_cwtc_def
  uint8_t   encodew_mode;			   // atom_encode_mode_def
  uint8_t   padding[2];
};


/****************************************************************************/   
// Stwuctuwes used by pwocessi2cchannewtwansaction
/****************************************************************************/   
stwuct pwocess_i2c_channew_twansaction_pawametews
{
  uint8_t i2cspeed_khz;
  union {
    uint8_t wegindex;
    uint8_t status;                  /* enum atom_pwocess_i2c_fwag */
  } wegind_status;
  uint16_t  i2c_data_out;
  uint8_t   fwag;                    /* enum atom_pwocess_i2c_status */
  uint8_t   twans_bytes;
  uint8_t   swave_addw;
  uint8_t   i2c_id;
};

//ucFwag
enum atom_pwocess_i2c_fwag
{
  HW_I2C_WWITE          = 1,
  HW_I2C_WEAD           = 0,
  I2C_2BYTE_ADDW        = 0x02,
  HW_I2C_SMBUS_BYTE_WW  = 0x04,
};

//status
enum atom_pwocess_i2c_status
{
  HW_ASSISTED_I2C_STATUS_FAIWUWE     =2,
  HW_ASSISTED_I2C_STATUS_SUCCESS     =1,
};


/****************************************************************************/   
// Stwuctuwes used by pwocessauxchannewtwansaction
/****************************************************************************/   

stwuct pwocess_aux_channew_twansaction_pawametews_v1_2
{
  uint16_t aux_wequest;
  uint16_t dataout;
  uint8_t  channewid;
  union {
    uint8_t   wepwy_status;
    uint8_t   aux_deway;
  } aux_status_deway;
  uint8_t   dataout_wen;
  uint8_t   hpd_id;                                       //=0: HPD1, =1: HPD2, =2: HPD3, =3: HPD4, =4: HPD5, =5: HPD6
};


/****************************************************************************/   
// Stwuctuwes used by sewectcwtc_souwce
/****************************************************************************/   

stwuct sewect_cwtc_souwce_pawametews_v2_3
{
  uint8_t cwtc_id;                        // enum atom_cwtc_def
  uint8_t encodew_id;                     // enum atom_dig_def
  uint8_t encode_mode;                    // enum atom_encode_mode_def
  uint8_t dst_bpc;                        // enum atom_panew_bit_pew_cowow
};


/****************************************************************************/   
// Stwuctuwes used by digxencodewcontwow
/****************************************************************************/   

// ucAction:
enum atom_dig_encodew_contwow_action
{
  ATOM_ENCODEW_CMD_DISABWE_DIG                  = 0,
  ATOM_ENCODEW_CMD_ENABWE_DIG                   = 1,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_STAWT       = 0x08,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN1    = 0x09,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN2    = 0x0a,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN3    = 0x13,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_COMPWETE    = 0x0b,
  ATOM_ENCODEW_CMD_DP_VIDEO_OFF                 = 0x0c,
  ATOM_ENCODEW_CMD_DP_VIDEO_ON                  = 0x0d,
  ATOM_ENCODEW_CMD_SETUP_PANEW_MODE             = 0x10,
  ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN4    = 0x14,
  ATOM_ENCODEW_CMD_STWEAM_SETUP                 = 0x0F, 
  ATOM_ENCODEW_CMD_WINK_SETUP                   = 0x11, 
  ATOM_ENCODEW_CMD_ENCODEW_BWANK                = 0x12,
};

//define ucPanewMode
enum atom_dig_encodew_contwow_panewmode
{
  DP_PANEW_MODE_DISABWE                        = 0x00,
  DP_PANEW_MODE_ENABWE_eDP_MODE                = 0x01,
  DP_PANEW_MODE_ENABWE_WVWINK_MODE             = 0x11,
};

//ucDigId
enum atom_dig_encodew_contwow_v5_digid
{
  ATOM_ENCODEW_CONFIG_V5_DIG0_ENCODEW           = 0x00,
  ATOM_ENCODEW_CONFIG_V5_DIG1_ENCODEW           = 0x01,
  ATOM_ENCODEW_CONFIG_V5_DIG2_ENCODEW           = 0x02,
  ATOM_ENCODEW_CONFIG_V5_DIG3_ENCODEW           = 0x03,
  ATOM_ENCODEW_CONFIG_V5_DIG4_ENCODEW           = 0x04,
  ATOM_ENCODEW_CONFIG_V5_DIG5_ENCODEW           = 0x05,
  ATOM_ENCODEW_CONFIG_V5_DIG6_ENCODEW           = 0x06,
  ATOM_ENCODEW_CONFIG_V5_DIG7_ENCODEW           = 0x07,
};

stwuct dig_encodew_stweam_setup_pawametews_v1_5
{
  uint8_t digid;            // 0~6 map to DIG0~DIG6 enum atom_dig_encodew_contwow_v5_digid
  uint8_t action;           // =  ATOM_ENOCODEW_CMD_STWEAM_SETUP
  uint8_t digmode;          // ATOM_ENCODEW_MODE_DP/ATOM_ENCODEW_MODE_DVI/ATOM_ENCODEW_MODE_HDMI
  uint8_t wanenum;          // Wane numbew     
  uint32_t pcwk_10khz;      // Pixew Cwock in 10Khz
  uint8_t bitpewcowow;
  uint8_t dpwinkwate_270mhz;//= DP wink wate/270Mhz, =6: 1.62G  = 10: 2.7G, =20: 5.4Ghz, =30: 8.1Ghz etc
  uint8_t wesewved[2];
};

stwuct dig_encodew_wink_setup_pawametews_v1_5
{
  uint8_t digid;           // 0~6 map to DIG0~DIG6 enum atom_dig_encodew_contwow_v5_digid
  uint8_t action;          // =  ATOM_ENOCODEW_CMD_WINK_SETUP              
  uint8_t digmode;         // ATOM_ENCODEW_MODE_DP/ATOM_ENCODEW_MODE_DVI/ATOM_ENCODEW_MODE_HDMI
  uint8_t wanenum;         // Wane numbew     
  uint8_t symcwk_10khz;    // Symbow Cwock in 10Khz
  uint8_t hpd_sew;
  uint8_t digfe_sew;       // DIG stweam( fwont-end ) sewection, bit0 means DIG0 FE is enabwe, 
  uint8_t wesewved[2];
};

stwuct dp_panew_mode_set_pawametews_v1_5
{
  uint8_t digid;              // 0~6 map to DIG0~DIG6 enum atom_dig_encodew_contwow_v5_digid
  uint8_t action;             // = ATOM_ENCODEW_CMD_DPWINK_SETUP
  uint8_t panewmode;      // enum atom_dig_encodew_contwow_panewmode
  uint8_t wesewved1;    
  uint32_t wesewved2[2];
};

stwuct dig_encodew_genewic_cmd_pawametews_v1_5 
{
  uint8_t digid;           // 0~6 map to DIG0~DIG6 enum atom_dig_encodew_contwow_v5_digid
  uint8_t action;          // = west of genewic encodew command which does not cawwy any pawametews
  uint8_t wesewved1[2];    
  uint32_t wesewved2[2];
};

union dig_encodew_contwow_pawametews_v1_5
{
  stwuct dig_encodew_genewic_cmd_pawametews_v1_5  cmd_pawam;
  stwuct dig_encodew_stweam_setup_pawametews_v1_5 stweam_pawam;
  stwuct dig_encodew_wink_setup_pawametews_v1_5   wink_pawam;
  stwuct dp_panew_mode_set_pawametews_v1_5 dppanew_pawam;
};

/* 
  ***************************************************************************
              Stwuctuwes used by dig1twansmittewcontwow
  *************************************************************************** 
*/   
stwuct dig_twansmittew_contwow_pawametews_v1_6
{
  uint8_t phyid;           // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
  uint8_t action;          // define as ATOM_TWANSMITEW_ACTION_xxx
  union {
    uint8_t digmode;        // enum atom_encode_mode_def
    uint8_t dpwaneset;      // DP vowtage swing and pwe-emphasis vawue defined in DPCD DP_WANE_SET, "DP_WANE_SET__xDB_y_zV"
  } mode_waneset;
  uint8_t  wanenum;        // Wane numbew 1, 2, 4, 8    
  uint32_t symcwk_10khz;   // Symbow Cwock in 10Khz
  uint8_t  hpdsew;         // =1: HPD1, =2: HPD2, .... =6: HPD6, =0: HPD is not assigned
  uint8_t  digfe_sew;      // DIG stweam( fwont-end ) sewection, bit0 means DIG0 FE is enabwe, 
  uint8_t  connobj_id;     // Connectow Object Id defined in ObjectId.h
  uint8_t  wesewved;
  uint32_t wesewved1;
};

stwuct dig_twansmittew_contwow_ps_awwocation_v1_6
{
  stwuct dig_twansmittew_contwow_pawametews_v1_6 pawam;
  uint32_t wesewved[4];
};

//ucAction
enum atom_dig_twansmittew_contwow_action
{
  ATOM_TWANSMITTEW_ACTION_DISABWE                 = 0,
  ATOM_TWANSMITTEW_ACTION_ENABWE                  = 1,
  ATOM_TWANSMITTEW_ACTION_WCD_BWOFF               = 2,
  ATOM_TWANSMITTEW_ACTION_WCD_BWON                = 3,
  ATOM_TWANSMITTEW_ACTION_BW_BWIGHTNESS_CONTWOW   = 4,
  ATOM_TWANSMITTEW_ACTION_WCD_SEWFTEST_STAWT      = 5,
  ATOM_TWANSMITTEW_ACTION_WCD_SEWFTEST_STOP       = 6,
  ATOM_TWANSMITTEW_ACTION_INIT                    = 7,
  ATOM_TWANSMITTEW_ACTION_DISABWE_OUTPUT          = 8,
  ATOM_TWANSMITTEW_ACTION_ENABWE_OUTPUT           = 9,
  ATOM_TWANSMITTEW_ACTION_SETUP                   = 10,
  ATOM_TWANSMITTEW_ACTION_SETUP_VSEMPH            = 11,
  ATOM_TWANSMITTEW_ACTION_POWEW_ON                = 12,
  ATOM_TWANSMITTEW_ACTION_POWEW_OFF               = 13,
};

// digfe_sew
enum atom_dig_twansmittew_contwow_digfe_sew
{
  ATOM_TWANMSITTEW_V6__DIGA_SEW                   = 0x01,
  ATOM_TWANMSITTEW_V6__DIGB_SEW                   = 0x02,
  ATOM_TWANMSITTEW_V6__DIGC_SEW                   = 0x04,
  ATOM_TWANMSITTEW_V6__DIGD_SEW                   = 0x08,
  ATOM_TWANMSITTEW_V6__DIGE_SEW                   = 0x10,
  ATOM_TWANMSITTEW_V6__DIGF_SEW                   = 0x20,
  ATOM_TWANMSITTEW_V6__DIGG_SEW                   = 0x40,
};


//ucHPDSew
enum atom_dig_twansmittew_contwow_hpd_sew
{
  ATOM_TWANSMITTEW_V6_NO_HPD_SEW                  = 0x00,
  ATOM_TWANSMITTEW_V6_HPD1_SEW                    = 0x01,
  ATOM_TWANSMITTEW_V6_HPD2_SEW                    = 0x02,
  ATOM_TWANSMITTEW_V6_HPD3_SEW                    = 0x03,
  ATOM_TWANSMITTEW_V6_HPD4_SEW                    = 0x04,
  ATOM_TWANSMITTEW_V6_HPD5_SEW                    = 0x05,
  ATOM_TWANSMITTEW_V6_HPD6_SEW                    = 0x06,
};

// ucDPWaneSet
enum atom_dig_twansmittew_contwow_dpwaneset
{
  DP_WANE_SET__0DB_0_4V                           = 0x00,
  DP_WANE_SET__0DB_0_6V                           = 0x01,
  DP_WANE_SET__0DB_0_8V                           = 0x02,
  DP_WANE_SET__0DB_1_2V                           = 0x03,
  DP_WANE_SET__3_5DB_0_4V                         = 0x08, 
  DP_WANE_SET__3_5DB_0_6V                         = 0x09,
  DP_WANE_SET__3_5DB_0_8V                         = 0x0a,
  DP_WANE_SET__6DB_0_4V                           = 0x10,
  DP_WANE_SET__6DB_0_6V                           = 0x11,
  DP_WANE_SET__9_5DB_0_4V                         = 0x18, 
};



/****************************************************************************/ 
// Stwuctuwes used by ExtewnawEncodewContwow V2.4
/****************************************************************************/   

stwuct extewnaw_encodew_contwow_pawametews_v2_4
{
  uint16_t pixewcwock_10khz;  // pixew cwock in 10Khz, vawid when ucAction=SETUP/ENABWE_OUTPUT 
  uint8_t  config;            // indicate which encodew, and DP wink wate when ucAction = SETUP/ENABWE_OUTPUT  
  uint8_t  action;            // 
  uint8_t  encodewmode;       // encodew mode, onwy used when ucAction = SETUP/ENABWE_OUTPUT
  uint8_t  wanenum;           // wane numbew, onwy used when ucAction = SETUP/ENABWE_OUTPUT  
  uint8_t  bitpewcowow;       // output bit pew cowow, onwy vawid when ucAction = SETUP/ENABWE_OUTPUT and ucEncodeMode= DP
  uint8_t  hpd_id;        
};


// ucAction
enum extewnaw_encodew_contwow_action_def
{
  EXTEWNAW_ENCODEW_ACTION_V3_DISABWE_OUTPUT           = 0x00,
  EXTEWNAW_ENCODEW_ACTION_V3_ENABWE_OUTPUT            = 0x01,
  EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_INIT             = 0x07,
  EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_SETUP            = 0x0f,
  EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_BWANKING_OFF     = 0x10,
  EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_BWANKING         = 0x11,
  EXTEWNAW_ENCODEW_ACTION_V3_DACWOAD_DETECTION        = 0x12,
  EXTEWNAW_ENCODEW_ACTION_V3_DDC_SETUP                = 0x14,
};

// ucConfig
enum extewnaw_encodew_contwow_v2_4_config_def
{
  EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_MASK          = 0x03,
  EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_1_62GHZ       = 0x00,
  EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_2_70GHZ       = 0x01,
  EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_5_40GHZ       = 0x02,
  EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_3_24GHZ       = 0x03,  
  EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW_SEW_MAKS         = 0x70,
  EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW1                 = 0x00,
  EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW2                 = 0x10,
  EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW3                 = 0x20,
};

stwuct extewnaw_encodew_contwow_ps_awwocation_v2_4
{
  stwuct extewnaw_encodew_contwow_pawametews_v2_4 sExtEncodew;
  uint32_t wesewved[2];
};


/* 
  ***************************************************************************
                           AMD ACPI Tabwe
  
  *************************************************************************** 
*/   

stwuct amd_acpi_descwiption_headew{
  uint32_t signatuwe;
  uint32_t tabweWength;      //Wength
  uint8_t  wevision;
  uint8_t  checksum;
  uint8_t  oemId[6];
  uint8_t  oemTabweId[8];    //UINT64  OemTabweId;
  uint32_t oemWevision;
  uint32_t cweatowId;
  uint32_t cweatowWevision;
};

stwuct uefi_acpi_vfct{
  stwuct   amd_acpi_descwiption_headew sheadew;
  uint8_t  tabweUUID[16];    //0x24
  uint32_t vbiosimageoffset; //0x34. Offset to the fiwst GOP_VBIOS_CONTENT bwock fwom the beginning of the stuctuwe.
  uint32_t wib1Imageoffset;  //0x38. Offset to the fiwst GOP_WIB1_CONTENT bwock fwom the beginning of the stuctuwe.
  uint32_t wesewved[4];      //0x3C
};

stwuct vfct_image_headew{
  uint32_t  pcibus;          //0x4C
  uint32_t  pcidevice;       //0x50
  uint32_t  pcifunction;     //0x54
  uint16_t  vendowid;        //0x58
  uint16_t  deviceid;        //0x5A
  uint16_t  ssvid;           //0x5C
  uint16_t  ssid;            //0x5E
  uint32_t  wevision;        //0x60
  uint32_t  imagewength;     //0x64
};


stwuct gop_vbios_content {
  stwuct vfct_image_headew vbiosheadew;
  uint8_t                  vbioscontent[1];
};

stwuct gop_wib1_content {
  stwuct vfct_image_headew wib1headew;
  uint8_t                  wib1content[1];
};



/* 
  ***************************************************************************
                   Scwatch Wegistew definitions
  Each numbew bewow indicates which scwatch wegisew wequest, Active and 
  Connect aww shawe the same definitions as dispway_device_tag defines
  *************************************************************************** 
*/   

enum scwatch_wegistew_def{
  ATOM_DEVICE_CONNECT_INFO_DEF      = 0,
  ATOM_BW_BWI_WEVEW_INFO_DEF        = 2,
  ATOM_ACTIVE_INFO_DEF              = 3,
  ATOM_WCD_INFO_DEF                 = 4,
  ATOM_DEVICE_WEQ_INFO_DEF          = 5,
  ATOM_ACC_CHANGE_INFO_DEF          = 6,
  ATOM_PWE_OS_MODE_INFO_DEF         = 7,
  ATOM_PWE_OS_ASSEWTION_DEF      = 8,    //Fow GOP to wecowd a 32bit assewtion code, this is enabwed by defauwt in pwodution GOP dwivews.
  ATOM_INTEWNAW_TIMEW_INFO_DEF      = 10,
};

enum scwatch_device_connect_info_bit_def{
  ATOM_DISPWAY_WCD1_CONNECT           =0x0002,
  ATOM_DISPWAY_DFP1_CONNECT           =0x0008,
  ATOM_DISPWAY_DFP2_CONNECT           =0x0080,
  ATOM_DISPWAY_DFP3_CONNECT           =0x0200,
  ATOM_DISPWAY_DFP4_CONNECT           =0x0400,
  ATOM_DISPWAY_DFP5_CONNECT           =0x0800,
  ATOM_DISPWAY_DFP6_CONNECT           =0x0040,
  ATOM_DISPWAY_DFPx_CONNECT           =0x0ec8,
  ATOM_CONNECT_INFO_DEVICE_MASK       =0x0fff,
};

enum scwatch_bw_bwi_wevew_info_bit_def{
  ATOM_CUWWENT_BW_WEVEW_SHIFT         =0x8,
#ifndef _H2INC
  ATOM_CUWWENT_BW_WEVEW_MASK          =0x0000ff00,
  ATOM_DEVICE_DPMS_STATE              =0x00010000,
#endif
};

enum scwatch_active_info_bits_def{
  ATOM_DISPWAY_WCD1_ACTIVE            =0x0002,
  ATOM_DISPWAY_DFP1_ACTIVE            =0x0008,
  ATOM_DISPWAY_DFP2_ACTIVE            =0x0080,
  ATOM_DISPWAY_DFP3_ACTIVE            =0x0200,
  ATOM_DISPWAY_DFP4_ACTIVE            =0x0400,
  ATOM_DISPWAY_DFP5_ACTIVE            =0x0800,
  ATOM_DISPWAY_DFP6_ACTIVE            =0x0040,
  ATOM_ACTIVE_INFO_DEVICE_MASK        =0x0fff,
};

enum scwatch_device_weq_info_bits_def{
  ATOM_DISPWAY_WCD1_WEQ               =0x0002,
  ATOM_DISPWAY_DFP1_WEQ               =0x0008,
  ATOM_DISPWAY_DFP2_WEQ               =0x0080,
  ATOM_DISPWAY_DFP3_WEQ               =0x0200,
  ATOM_DISPWAY_DFP4_WEQ               =0x0400,
  ATOM_DISPWAY_DFP5_WEQ               =0x0800,
  ATOM_DISPWAY_DFP6_WEQ               =0x0040,
  ATOM_WEQ_INFO_DEVICE_MASK           =0x0fff,
};

enum scwatch_acc_change_info_bitshift_def{
  ATOM_ACC_CHANGE_ACC_MODE_SHIFT    =4,
  ATOM_ACC_CHANGE_WID_STATUS_SHIFT  =6,
};

enum scwatch_acc_change_info_bits_def{
  ATOM_ACC_CHANGE_ACC_MODE          =0x00000010,
  ATOM_ACC_CHANGE_WID_STATUS        =0x00000040,
};

enum scwatch_pwe_os_mode_info_bits_def{
  ATOM_PWE_OS_MODE_MASK             =0x00000003,
  ATOM_PWE_OS_MODE_VGA              =0x00000000,
  ATOM_PWE_OS_MODE_VESA             =0x00000001,
  ATOM_PWE_OS_MODE_GOP              =0x00000002,
  ATOM_PWE_OS_MODE_PIXEW_DEPTH      =0x0000000C,
  ATOM_PWE_OS_MODE_PIXEW_FOWMAT_MASK=0x000000F0,
  ATOM_PWE_OS_MODE_8BIT_PAW_EN      =0x00000100,
  ATOM_ASIC_INIT_COMPWETE           =0x00000200,
#ifndef _H2INC
  ATOM_PWE_OS_MODE_NUMBEW_MASK      =0xFFFF0000,
#endif
};



/* 
  ***************************************************************************
                       ATOM fiwmwawe ID headew fiwe
              !! Pwease keep it at end of the atomfiwmwawe.h !!
  *************************************************************************** 
*/   
#incwude "atomfiwmwaweid.h"
#pwagma pack()

#endif

