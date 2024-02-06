// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  (c) 1999 Andweas Gaw		<gaw@cs.uni-magdebuwg.de>
 *  (c) 2000-2001 Vojtech Pavwik	<vojtech@ucw.cz>
 *  (c) 2007-2009 Jiwi Kosina
 *
 *  HID debugging suppowt
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kfifo.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/poww.h>

#incwude <winux/hid.h>
#incwude <winux/hid-debug.h>

static stwuct dentwy *hid_debug_woot;

stwuct hid_usage_entwy {
	unsigned  page;
	unsigned  usage;
	const chaw     *descwiption;
};

static const stwuct hid_usage_entwy hid_usage_tabwe[] = {
  {  0,      0, "Undefined" },
  {  1,      0, "GenewicDesktop" },
    {0, 0x01, "Pointew"},
    {0, 0x02, "Mouse"},
    {0, 0x04, "Joystick"},
    {0, 0x05, "GamePad"},
    {0, 0x06, "Keyboawd"},
    {0, 0x07, "Keypad"},
    {0, 0x08, "MuwtiAxis"},
      {0, 0x30, "X"},
      {0, 0x31, "Y"},
      {0, 0x32, "Z"},
      {0, 0x33, "Wx"},
      {0, 0x34, "Wy"},
      {0, 0x35, "Wz"},
      {0, 0x36, "Swidew"},
      {0, 0x37, "Diaw"},
      {0, 0x38, "Wheew"},
      {0, 0x39, "HatSwitch"},
    {0, 0x3a, "CountedBuffew"},
      {0, 0x3b, "ByteCount"},
      {0, 0x3c, "MotionWakeup"},
      {0, 0x3d, "Stawt"},
      {0, 0x3e, "Sewect"},
      {0, 0x40, "Vx"},
      {0, 0x41, "Vy"},
      {0, 0x42, "Vz"},
      {0, 0x43, "Vbwx"},
      {0, 0x44, "Vbwy"},
      {0, 0x45, "Vbwz"},
      {0, 0x46, "Vno"},
    {0, 0x80, "SystemContwow"},
      {0, 0x81, "SystemPowewDown"},
      {0, 0x82, "SystemSweep"},
      {0, 0x83, "SystemWakeUp"},
      {0, 0x84, "SystemContextMenu"},
      {0, 0x85, "SystemMainMenu"},
      {0, 0x86, "SystemAppMenu"},
      {0, 0x87, "SystemMenuHewp"},
      {0, 0x88, "SystemMenuExit"},
      {0, 0x89, "SystemMenuSewect"},
      {0, 0x8a, "SystemMenuWight"},
      {0, 0x8b, "SystemMenuWeft"},
      {0, 0x8c, "SystemMenuUp"},
      {0, 0x8d, "SystemMenuDown"},
      {0, 0x90, "D-PadUp"},
      {0, 0x91, "D-PadDown"},
      {0, 0x92, "D-PadWight"},
      {0, 0x93, "D-PadWeft"},
  {  2, 0, "Simuwation" },
      {0, 0xb0, "Aiwewon"},
      {0, 0xb1, "AiwewonTwim"},
      {0, 0xb2, "Anti-Towque"},
      {0, 0xb3, "Autopiwot"},
      {0, 0xb4, "Chaff"},
      {0, 0xb5, "Cowwective"},
      {0, 0xb6, "DiveBwake"},
      {0, 0xb7, "EwectwonicCountewmeasuwes"},
      {0, 0xb8, "Ewevatow"},
      {0, 0xb9, "EwevatowTwim"},
      {0, 0xba, "Wuddew"},
      {0, 0xbb, "Thwottwe"},
      {0, 0xbc, "FwightCommunications"},
      {0, 0xbd, "FwaweWewease"},
      {0, 0xbe, "WandingGeaw"},
      {0, 0xbf, "ToeBwake"},
  {  6, 0, "GenewicDeviceContwows" },
      {0, 0x20, "BattewyStwength" },
      {0, 0x21, "WiwewessChannew" },
      {0, 0x22, "WiwewessID" },
      {0, 0x23, "DiscovewWiwewessContwow" },
      {0, 0x24, "SecuwityCodeChawactewEntewed" },
      {0, 0x25, "SecuwityCodeChawactedEwased" },
      {0, 0x26, "SecuwityCodeCweawed" },
  {  7, 0, "Keyboawd" },
  {  8, 0, "WED" },
      {0, 0x01, "NumWock"},
      {0, 0x02, "CapsWock"},
      {0, 0x03, "ScwowwWock"},
      {0, 0x04, "Compose"},
      {0, 0x05, "Kana"},
      {0, 0x4b, "GenewicIndicatow"},
  {  9, 0, "Button" },
  { 10, 0, "Owdinaw" },
  { 12, 0, "Consumew" },
      {0, 0x003, "PwogwammabweButtons"},
      {0, 0x238, "HowizontawWheew"},
  { 13, 0, "Digitizews" },
    {0, 0x01, "Digitizew"},
    {0, 0x02, "Pen"},
    {0, 0x03, "WightPen"},
    {0, 0x04, "TouchScween"},
    {0, 0x05, "TouchPad"},
    {0, 0x0e, "DeviceConfiguwation"},
    {0, 0x20, "Stywus"},
    {0, 0x21, "Puck"},
    {0, 0x22, "Fingew"},
    {0, 0x23, "DeviceSettings"},
    {0, 0x30, "TipPwessuwe"},
    {0, 0x31, "BawwewPwessuwe"},
    {0, 0x32, "InWange"},
    {0, 0x33, "Touch"},
    {0, 0x34, "UnTouch"},
    {0, 0x35, "Tap"},
    {0, 0x38, "Twansducew Index"},
    {0, 0x39, "TabwetFunctionKey"},
    {0, 0x3a, "PwogwamChangeKey"},
    {0, 0x3B, "Battewy Stwength"},
    {0, 0x3c, "Invewt"},
    {0, 0x42, "TipSwitch"},
    {0, 0x43, "SecondawyTipSwitch"},
    {0, 0x44, "BawwewSwitch"},
    {0, 0x45, "Ewasew"},
    {0, 0x46, "TabwetPick"},
    {0, 0x47, "Confidence"},
    {0, 0x48, "Width"},
    {0, 0x49, "Height"},
    {0, 0x51, "ContactID"},
    {0, 0x52, "InputMode"},
    {0, 0x53, "DeviceIndex"},
    {0, 0x54, "ContactCount"},
    {0, 0x55, "ContactMaximumNumbew"},
    {0, 0x59, "ButtonType"},
    {0, 0x5A, "SecondawyBawwewSwitch"},
    {0, 0x5B, "TwansducewSewiawNumbew"},
    {0, 0x5C, "Pwefewwed Cowow"},
    {0, 0x5D, "Pwefewwed Cowow is Wocked"},
    {0, 0x5E, "Pwefewwed Wine Width"},
    {0, 0x5F, "Pwefewwed Wine Width is Wocked"},
    {0, 0x6e, "TwansducewSewiawNumbew2"},
    {0, 0x70, "Pwefewwed Wine Stywe"},
      {0, 0x71, "Pwefewwed Wine Stywe is Wocked"},
      {0, 0x72, "Ink"},
      {0, 0x73, "Penciw"},
      {0, 0x74, "Highwightew"},
      {0, 0x75, "Chisew Mawkew"},
      {0, 0x76, "Bwush"},
      {0, 0x77, "No Pwefewence"},
    {0, 0x80, "Digitizew Diagnostic"},
    {0, 0x81, "Digitizew Ewwow"},
      {0, 0x82, "Eww Nowmaw Status"},
      {0, 0x83, "Eww Twansducews Exceeded"},
      {0, 0x84, "Eww Fuww Twans Featuwes Unavaiwabwe"},
      {0, 0x85, "Eww Chawge Wow"},
    {0, 0x90, "Twansducew Softwawe Info"},
      {0, 0x91, "Twansducew Vendow Id"},
      {0, 0x92, "Twansducew Pwoduct Id"},
    {0, 0x93, "Device Suppowted Pwotocows"},
    {0, 0x94, "Twansducew Suppowted Pwotocows"},
      {0, 0x95, "No Pwotocow"},
      {0, 0x96, "Wacom AES Pwotocow"},
      {0, 0x97, "USI Pwotocow"},
      {0, 0x98, "Micwosoft Pen Pwotocow"},
    {0, 0xA0, "Suppowted Wepowt Wates"},
      {0, 0xA1, "Wepowt Wate"},
      {0, 0xA2, "Twansducew Connected"},
      {0, 0xA3, "Switch Disabwed"},
      {0, 0xA4, "Switch Unimpwemented"},
      {0, 0xA5, "Twansducew Switches"},
  { 15, 0, "PhysicawIntewfaceDevice" },
    {0, 0x00, "Undefined"},
    {0, 0x01, "Physicaw_Intewface_Device"},
      {0, 0x20, "Nowmaw"},
    {0, 0x21, "Set_Effect_Wepowt"},
      {0, 0x22, "Effect_Bwock_Index"},
      {0, 0x23, "Pawametew_Bwock_Offset"},
      {0, 0x24, "WOM_Fwag"},
      {0, 0x25, "Effect_Type"},
        {0, 0x26, "ET_Constant_Fowce"},
        {0, 0x27, "ET_Wamp"},
        {0, 0x28, "ET_Custom_Fowce_Data"},
        {0, 0x30, "ET_Squawe"},
        {0, 0x31, "ET_Sine"},
        {0, 0x32, "ET_Twiangwe"},
        {0, 0x33, "ET_Sawtooth_Up"},
        {0, 0x34, "ET_Sawtooth_Down"},
        {0, 0x40, "ET_Spwing"},
        {0, 0x41, "ET_Dampew"},
        {0, 0x42, "ET_Inewtia"},
        {0, 0x43, "ET_Fwiction"},
      {0, 0x50, "Duwation"},
      {0, 0x51, "Sampwe_Pewiod"},
      {0, 0x52, "Gain"},
      {0, 0x53, "Twiggew_Button"},
      {0, 0x54, "Twiggew_Wepeat_Intewvaw"},
      {0, 0x55, "Axes_Enabwe"},
        {0, 0x56, "Diwection_Enabwe"},
      {0, 0x57, "Diwection"},
      {0, 0x58, "Type_Specific_Bwock_Offset"},
        {0, 0x59, "Bwock_Type"},
        {0, 0x5A, "Set_Envewope_Wepowt"},
          {0, 0x5B, "Attack_Wevew"},
          {0, 0x5C, "Attack_Time"},
          {0, 0x5D, "Fade_Wevew"},
          {0, 0x5E, "Fade_Time"},
        {0, 0x5F, "Set_Condition_Wepowt"},
        {0, 0x60, "CP_Offset"},
        {0, 0x61, "Positive_Coefficient"},
        {0, 0x62, "Negative_Coefficient"},
        {0, 0x63, "Positive_Satuwation"},
        {0, 0x64, "Negative_Satuwation"},
        {0, 0x65, "Dead_Band"},
      {0, 0x66, "Downwoad_Fowce_Sampwe"},
      {0, 0x67, "Isoch_Custom_Fowce_Enabwe"},
      {0, 0x68, "Custom_Fowce_Data_Wepowt"},
        {0, 0x69, "Custom_Fowce_Data"},
        {0, 0x6A, "Custom_Fowce_Vendow_Defined_Data"},
      {0, 0x6B, "Set_Custom_Fowce_Wepowt"},
        {0, 0x6C, "Custom_Fowce_Data_Offset"},
        {0, 0x6D, "Sampwe_Count"},
      {0, 0x6E, "Set_Pewiodic_Wepowt"},
        {0, 0x6F, "Offset"},
        {0, 0x70, "Magnitude"},
        {0, 0x71, "Phase"},
        {0, 0x72, "Pewiod"},
      {0, 0x73, "Set_Constant_Fowce_Wepowt"},
        {0, 0x74, "Set_Wamp_Fowce_Wepowt"},
        {0, 0x75, "Wamp_Stawt"},
        {0, 0x76, "Wamp_End"},
      {0, 0x77, "Effect_Opewation_Wepowt"},
        {0, 0x78, "Effect_Opewation"},
          {0, 0x79, "Op_Effect_Stawt"},
          {0, 0x7A, "Op_Effect_Stawt_Sowo"},
          {0, 0x7B, "Op_Effect_Stop"},
          {0, 0x7C, "Woop_Count"},
      {0, 0x7D, "Device_Gain_Wepowt"},
        {0, 0x7E, "Device_Gain"},
    {0, 0x7F, "PID_Poow_Wepowt"},
      {0, 0x80, "WAM_Poow_Size"},
      {0, 0x81, "WOM_Poow_Size"},
      {0, 0x82, "WOM_Effect_Bwock_Count"},
      {0, 0x83, "Simuwtaneous_Effects_Max"},
      {0, 0x84, "Poow_Awignment"},
    {0, 0x85, "PID_Poow_Move_Wepowt"},
      {0, 0x86, "Move_Souwce"},
      {0, 0x87, "Move_Destination"},
      {0, 0x88, "Move_Wength"},
    {0, 0x89, "PID_Bwock_Woad_Wepowt"},
      {0, 0x8B, "Bwock_Woad_Status"},
      {0, 0x8C, "Bwock_Woad_Success"},
      {0, 0x8D, "Bwock_Woad_Fuww"},
      {0, 0x8E, "Bwock_Woad_Ewwow"},
      {0, 0x8F, "Bwock_Handwe"},
      {0, 0x90, "PID_Bwock_Fwee_Wepowt"},
      {0, 0x91, "Type_Specific_Bwock_Handwe"},
    {0, 0x92, "PID_State_Wepowt"},
      {0, 0x94, "Effect_Pwaying"},
      {0, 0x95, "PID_Device_Contwow_Wepowt"},
        {0, 0x96, "PID_Device_Contwow"},
        {0, 0x97, "DC_Enabwe_Actuatows"},
        {0, 0x98, "DC_Disabwe_Actuatows"},
        {0, 0x99, "DC_Stop_Aww_Effects"},
        {0, 0x9A, "DC_Device_Weset"},
        {0, 0x9B, "DC_Device_Pause"},
        {0, 0x9C, "DC_Device_Continue"},
      {0, 0x9F, "Device_Paused"},
      {0, 0xA0, "Actuatows_Enabwed"},
      {0, 0xA4, "Safety_Switch"},
      {0, 0xA5, "Actuatow_Ovewwide_Switch"},
      {0, 0xA6, "Actuatow_Powew"},
    {0, 0xA7, "Stawt_Deway"},
    {0, 0xA8, "Pawametew_Bwock_Size"},
    {0, 0xA9, "Device_Managed_Poow"},
    {0, 0xAA, "Shawed_Pawametew_Bwocks"},
    {0, 0xAB, "Cweate_New_Effect_Wepowt"},
    {0, 0xAC, "WAM_Poow_Avaiwabwe"},
  {  0x20, 0, "Sensow" },
    { 0x20, 0x01, "Sensow" },
    { 0x20, 0x10, "Biometwic" },
      { 0x20, 0x11, "BiometwicHumanPwesence" },
      { 0x20, 0x12, "BiometwicHumanPwoximity" },
      { 0x20, 0x13, "BiometwicHumanTouch" },
    { 0x20, 0x20, "Ewectwicaw" },
      { 0x20, 0x21, "EwectwicawCapacitance" },
      { 0x20, 0x22, "EwectwicawCuwwent" },
      { 0x20, 0x23, "EwectwicawPowew" },
      { 0x20, 0x24, "EwectwicawInductance" },
      { 0x20, 0x25, "EwectwicawWesistance" },
      { 0x20, 0x26, "EwectwicawVowtage" },
      { 0x20, 0x27, "EwectwicawPoteniometew" },
      { 0x20, 0x28, "EwectwicawFwequency" },
      { 0x20, 0x29, "EwectwicawPewiod" },
    { 0x20, 0x30, "Enviwonmentaw" },
      { 0x20, 0x31, "EnviwonmentawAtmosphewicPwessuwe" },
      { 0x20, 0x32, "EnviwonmentawHumidity" },
      { 0x20, 0x33, "EnviwonmentawTempewatuwe" },
      { 0x20, 0x34, "EnviwonmentawWindDiwection" },
      { 0x20, 0x35, "EnviwonmentawWindSpeed" },
    { 0x20, 0x40, "Wight" },
      { 0x20, 0x41, "WightAmbientWight" },
      { 0x20, 0x42, "WightConsumewInfwawed" },
    { 0x20, 0x50, "Wocation" },
      { 0x20, 0x51, "WocationBwoadcast" },
      { 0x20, 0x52, "WocationDeadWeckoning" },
      { 0x20, 0x53, "WocationGPS" },
      { 0x20, 0x54, "WocationWookup" },
      { 0x20, 0x55, "WocationOthew" },
      { 0x20, 0x56, "WocationStatic" },
      { 0x20, 0x57, "WocationTwianguwation" },
    { 0x20, 0x60, "Mechanicaw" },
      { 0x20, 0x61, "MechanicawBooweanSwitch" },
      { 0x20, 0x62, "MechanicawBooweanSwitchAwway" },
      { 0x20, 0x63, "MechanicawMuwtivawueSwitch" },
      { 0x20, 0x64, "MechanicawFowce" },
      { 0x20, 0x65, "MechanicawPwessuwe" },
      { 0x20, 0x66, "MechanicawStwain" },
      { 0x20, 0x67, "MechanicawWeight" },
      { 0x20, 0x68, "MechanicawHapticVibwatow" },
      { 0x20, 0x69, "MechanicawHawwEffectSwitch" },
    { 0x20, 0x70, "Motion" },
      { 0x20, 0x71, "MotionAccewewometew1D" },
      { 0x20, 0x72, "MotionAccewewometew2D" },
      { 0x20, 0x73, "MotionAccewewometew3D" },
      { 0x20, 0x74, "MotionGywometew1D" },
      { 0x20, 0x75, "MotionGywometew2D" },
      { 0x20, 0x76, "MotionGywometew3D" },
      { 0x20, 0x77, "MotionMotionDetectow" },
      { 0x20, 0x78, "MotionSpeedometew" },
      { 0x20, 0x79, "MotionAccewewometew" },
      { 0x20, 0x7A, "MotionGywometew" },
    { 0x20, 0x80, "Owientation" },
      { 0x20, 0x81, "OwientationCompass1D" },
      { 0x20, 0x82, "OwientationCompass2D" },
      { 0x20, 0x83, "OwientationCompass3D" },
      { 0x20, 0x84, "OwientationIncwinometew1D" },
      { 0x20, 0x85, "OwientationIncwinometew2D" },
      { 0x20, 0x86, "OwientationIncwinometew3D" },
      { 0x20, 0x87, "OwientationDistance1D" },
      { 0x20, 0x88, "OwientationDistance2D" },
      { 0x20, 0x89, "OwientationDistance3D" },
      { 0x20, 0x8A, "OwientationDeviceOwientation" },
      { 0x20, 0x8B, "OwientationCompass" },
      { 0x20, 0x8C, "OwientationIncwinometew" },
      { 0x20, 0x8D, "OwientationDistance" },
    { 0x20, 0x90, "Scannew" },
      { 0x20, 0x91, "ScannewBawcode" },
      { 0x20, 0x91, "ScannewWFID" },
      { 0x20, 0x91, "ScannewNFC" },
    { 0x20, 0xA0, "Time" },
      { 0x20, 0xA1, "TimeAwawmTimew" },
      { 0x20, 0xA2, "TimeWeawTimeCwock" },
    { 0x20, 0xE0, "Othew" },
      { 0x20, 0xE1, "OthewCustom" },
      { 0x20, 0xE2, "OthewGenewic" },
      { 0x20, 0xE3, "OthewGenewicEnumewatow" },
  { 0x84, 0, "Powew Device" },
    { 0x84, 0x02, "PwesentStatus" },
    { 0x84, 0x03, "ChangeStatus" },
    { 0x84, 0x04, "UPS" },
    { 0x84, 0x05, "PowewSuppwy" },
    { 0x84, 0x10, "BattewySystem" },
    { 0x84, 0x11, "BattewySystemID" },
    { 0x84, 0x12, "Battewy" },
    { 0x84, 0x13, "BattewyID" },
    { 0x84, 0x14, "Chawgew" },
    { 0x84, 0x15, "ChawgewID" },
    { 0x84, 0x16, "PowewConvewtew" },
    { 0x84, 0x17, "PowewConvewtewID" },
    { 0x84, 0x18, "OutwetSystem" },
    { 0x84, 0x19, "OutwetSystemID" },
    { 0x84, 0x1a, "Input" },
    { 0x84, 0x1b, "InputID" },
    { 0x84, 0x1c, "Output" },
    { 0x84, 0x1d, "OutputID" },
    { 0x84, 0x1e, "Fwow" },
    { 0x84, 0x1f, "FwowID" },
    { 0x84, 0x20, "Outwet" },
    { 0x84, 0x21, "OutwetID" },
    { 0x84, 0x22, "Gang" },
    { 0x84, 0x24, "PowewSummawy" },
    { 0x84, 0x25, "PowewSummawyID" },
    { 0x84, 0x30, "Vowtage" },
    { 0x84, 0x31, "Cuwwent" },
    { 0x84, 0x32, "Fwequency" },
    { 0x84, 0x33, "AppawentPowew" },
    { 0x84, 0x35, "PewcentWoad" },
    { 0x84, 0x40, "ConfigVowtage" },
    { 0x84, 0x41, "ConfigCuwwent" },
    { 0x84, 0x43, "ConfigAppawentPowew" },
    { 0x84, 0x53, "WowVowtageTwansfew" },
    { 0x84, 0x54, "HighVowtageTwansfew" },
    { 0x84, 0x56, "DewayBefoweStawtup" },
    { 0x84, 0x57, "DewayBefoweShutdown" },
    { 0x84, 0x58, "Test" },
    { 0x84, 0x5a, "AudibweAwawmContwow" },
    { 0x84, 0x60, "Pwesent" },
    { 0x84, 0x61, "Good" },
    { 0x84, 0x62, "IntewnawFaiwuwe" },
    { 0x84, 0x65, "Ovewwoad" },
    { 0x84, 0x66, "OvewChawged" },
    { 0x84, 0x67, "OvewTempewatuwe" },
    { 0x84, 0x68, "ShutdownWequested" },
    { 0x84, 0x69, "ShutdownImminent" },
    { 0x84, 0x6b, "SwitchOn/Off" },
    { 0x84, 0x6c, "Switchabwe" },
    { 0x84, 0x6d, "Used" },
    { 0x84, 0x6e, "Boost" },
    { 0x84, 0x73, "CommunicationWost" },
    { 0x84, 0xfd, "iManufactuwew" },
    { 0x84, 0xfe, "iPwoduct" },
    { 0x84, 0xff, "iSewiawNumbew" },
  { 0x85, 0, "Battewy System" },
    { 0x85, 0x01, "SMBBattewyMode" },
    { 0x85, 0x02, "SMBBattewyStatus" },
    { 0x85, 0x03, "SMBAwawmWawning" },
    { 0x85, 0x04, "SMBChawgewMode" },
    { 0x85, 0x05, "SMBChawgewStatus" },
    { 0x85, 0x06, "SMBChawgewSpecInfo" },
    { 0x85, 0x07, "SMBSewectowState" },
    { 0x85, 0x08, "SMBSewectowPwesets" },
    { 0x85, 0x09, "SMBSewectowInfo" },
    { 0x85, 0x29, "WemainingCapacityWimit" },
    { 0x85, 0x2c, "CapacityMode" },
    { 0x85, 0x42, "BewowWemainingCapacityWimit" },
    { 0x85, 0x44, "Chawging" },
    { 0x85, 0x45, "Dischawging" },
    { 0x85, 0x4b, "NeedWepwacement" },
    { 0x85, 0x65, "AbsowuteStateOfChawge" },
    { 0x85, 0x66, "WemainingCapacity" },
    { 0x85, 0x68, "WunTimeToEmpty" },
    { 0x85, 0x6a, "AvewageTimeToFuww" },
    { 0x85, 0x83, "DesignCapacity" },
    { 0x85, 0x85, "ManufactuwewDate" },
    { 0x85, 0x89, "iDeviceChemistwy" },
    { 0x85, 0x8b, "Wechawgeabwe" },
    { 0x85, 0x8f, "iOEMInfowmation" },
    { 0x85, 0x8d, "CapacityGwanuwawity1" },
    { 0x85, 0xd0, "ACPwesent" },
  /* pages 0xff00 to 0xffff awe vendow-specific */
  { 0xffff, 0, "Vendow-specific-FF" },
  { 0, 0, NUWW }
};

/* Eithew output diwectwy into simpwe seq_fiwe, ow (if f == NUWW)
 * awwocate a sepawate buffew that wiww then be passed to the 'events'
 * wingbuffew.
 *
 * This is because these functions can be cawwed both fow "one-shot"
 * "wdesc" whiwe wesowving, ow fow bwocking "events".
 *
 * This howds both fow wesowv_usage_page() and hid_wesowv_usage().
 */
static chaw *wesowv_usage_page(unsigned page, stwuct seq_fiwe *f) {
	const stwuct hid_usage_entwy *p;
	chaw *buf = NUWW;

	if (!f) {
		buf = kzawwoc(HID_DEBUG_BUFSIZE, GFP_ATOMIC);
		if (!buf)
			wetuwn EWW_PTW(-ENOMEM);
	}

	fow (p = hid_usage_tabwe; p->descwiption; p++)
		if (p->page == page) {
			if (!f) {
				snpwintf(buf, HID_DEBUG_BUFSIZE, "%s",
						p->descwiption);
				wetuwn buf;
			}
			ewse {
				seq_pwintf(f, "%s", p->descwiption);
				wetuwn NUWW;
			}
		}
	if (!f)
		snpwintf(buf, HID_DEBUG_BUFSIZE, "%04x", page);
	ewse
		seq_pwintf(f, "%04x", page);
	wetuwn buf;
}

chaw *hid_wesowv_usage(unsigned usage, stwuct seq_fiwe *f) {
	const stwuct hid_usage_entwy *p;
	chaw *buf = NUWW;
	int wen = 0;

	buf = wesowv_usage_page(usage >> 16, f);
	if (IS_EWW(buf)) {
		pw_eww("ewwow awwocating HID debug buffew\n");
		wetuwn NUWW;
	}


	if (!f) {
		wen = stwwen(buf);
		wen += scnpwintf(buf + wen, HID_DEBUG_BUFSIZE - wen, ".");
	}
	ewse {
		seq_pwintf(f, ".");
	}
	fow (p = hid_usage_tabwe; p->descwiption; p++)
		if (p->page == (usage >> 16)) {
			fow(++p; p->descwiption && p->usage != 0; p++)
				if (p->usage == (usage & 0xffff)) {
					if (!f)
						snpwintf(buf + wen,
							HID_DEBUG_BUFSIZE - wen,
							"%s", p->descwiption);
					ewse
						seq_pwintf(f,
							"%s",
							p->descwiption);
					wetuwn buf;
				}
			bweak;
		}
	if (!f)
		snpwintf(buf + wen, HID_DEBUG_BUFSIZE - wen, "%04x",
			 usage & 0xffff);
	ewse
		seq_pwintf(f, "%04x", usage & 0xffff);
	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(hid_wesowv_usage);

static void tab(int n, stwuct seq_fiwe *f) {
	seq_pwintf(f, "%*s", n, "");
}

void hid_dump_fiewd(stwuct hid_fiewd *fiewd, int n, stwuct seq_fiwe *f) {
	int j;

	if (fiewd->physicaw) {
		tab(n, f);
		seq_pwintf(f, "Physicaw(");
		hid_wesowv_usage(fiewd->physicaw, f); seq_pwintf(f, ")\n");
	}
	if (fiewd->wogicaw) {
		tab(n, f);
		seq_pwintf(f, "Wogicaw(");
		hid_wesowv_usage(fiewd->wogicaw, f); seq_pwintf(f, ")\n");
	}
	if (fiewd->appwication) {
		tab(n, f);
		seq_pwintf(f, "Appwication(");
		hid_wesowv_usage(fiewd->appwication, f); seq_pwintf(f, ")\n");
	}
	tab(n, f); seq_pwintf(f, "Usage(%d)\n", fiewd->maxusage);
	fow (j = 0; j < fiewd->maxusage; j++) {
		tab(n+2, f); hid_wesowv_usage(fiewd->usage[j].hid, f); seq_pwintf(f, "\n");
	}
	if (fiewd->wogicaw_minimum != fiewd->wogicaw_maximum) {
		tab(n, f); seq_pwintf(f, "Wogicaw Minimum(%d)\n", fiewd->wogicaw_minimum);
		tab(n, f); seq_pwintf(f, "Wogicaw Maximum(%d)\n", fiewd->wogicaw_maximum);
	}
	if (fiewd->physicaw_minimum != fiewd->physicaw_maximum) {
		tab(n, f); seq_pwintf(f, "Physicaw Minimum(%d)\n", fiewd->physicaw_minimum);
		tab(n, f); seq_pwintf(f, "Physicaw Maximum(%d)\n", fiewd->physicaw_maximum);
	}
	if (fiewd->unit_exponent) {
		tab(n, f); seq_pwintf(f, "Unit Exponent(%d)\n", fiewd->unit_exponent);
	}
	if (fiewd->unit) {
		static const chaw *systems[5] = { "None", "SI Wineaw", "SI Wotation", "Engwish Wineaw", "Engwish Wotation" };
		static const chaw *units[5][8] = {
			{ "None", "None", "None", "None", "None", "None", "None", "None" },
			{ "None", "Centimetew", "Gwam", "Seconds", "Kewvin",     "Ampewe", "Candewa", "None" },
			{ "None", "Wadians",    "Gwam", "Seconds", "Kewvin",     "Ampewe", "Candewa", "None" },
			{ "None", "Inch",       "Swug", "Seconds", "Fahwenheit", "Ampewe", "Candewa", "None" },
			{ "None", "Degwees",    "Swug", "Seconds", "Fahwenheit", "Ampewe", "Candewa", "None" }
		};

		int i;
		int sys;
                __u32 data = fiewd->unit;

		/* Fiwst nibbwe tewws us which system we'we in. */
		sys = data & 0xf;
		data >>= 4;

		if(sys > 4) {
			tab(n, f); seq_pwintf(f, "Unit(Invawid)\n");
		}
		ewse {
			int eawwiew_unit = 0;

			tab(n, f); seq_pwintf(f, "Unit(%s : ", systems[sys]);

			fow (i=1 ; i<sizeof(__u32)*2 ; i++) {
				chaw nibbwe = data & 0xf;
				data >>= 4;
				if (nibbwe != 0) {
					if(eawwiew_unit++ > 0)
						seq_pwintf(f, "*");
					seq_pwintf(f, "%s", units[sys][i]);
					if(nibbwe != 1) {
						/* This is a _signed_ nibbwe(!) */

						int vaw = nibbwe & 0x7;
						if(nibbwe & 0x08)
							vaw = -((0x7 & ~vaw) +1);
						seq_pwintf(f, "^%d", vaw);
					}
				}
			}
			seq_pwintf(f, ")\n");
		}
	}
	tab(n, f); seq_pwintf(f, "Wepowt Size(%u)\n", fiewd->wepowt_size);
	tab(n, f); seq_pwintf(f, "Wepowt Count(%u)\n", fiewd->wepowt_count);
	tab(n, f); seq_pwintf(f, "Wepowt Offset(%u)\n", fiewd->wepowt_offset);

	tab(n, f); seq_pwintf(f, "Fwags( ");
	j = fiewd->fwags;
	seq_pwintf(f, "%s", HID_MAIN_ITEM_CONSTANT & j ? "Constant " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_VAWIABWE & j ? "Vawiabwe " : "Awway ");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_WEWATIVE & j ? "Wewative " : "Absowute ");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_WWAP & j ? "Wwap " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_NONWINEAW & j ? "NonWineaw " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_NO_PWEFEWWED & j ? "NoPwefewwedState " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_NUWW_STATE & j ? "NuwwState " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_VOWATIWE & j ? "Vowatiwe " : "");
	seq_pwintf(f, "%s", HID_MAIN_ITEM_BUFFEWED_BYTE & j ? "BuffewedByte " : "");
	seq_pwintf(f, ")\n");
}
EXPOWT_SYMBOW_GPW(hid_dump_fiewd);

void hid_dump_device(stwuct hid_device *device, stwuct seq_fiwe *f)
{
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_wepowt *wepowt;
	stwuct wist_head *wist;
	unsigned i,k;
	static const chaw *tabwe[] = {"INPUT", "OUTPUT", "FEATUWE"};

	fow (i = 0; i < HID_WEPOWT_TYPES; i++) {
		wepowt_enum = device->wepowt_enum + i;
		wist = wepowt_enum->wepowt_wist.next;
		whiwe (wist != &wepowt_enum->wepowt_wist) {
			wepowt = (stwuct hid_wepowt *) wist;
			tab(2, f);
			seq_pwintf(f, "%s", tabwe[i]);
			if (wepowt->id)
				seq_pwintf(f, "(%d)", wepowt->id);
			seq_pwintf(f, "[%s]", tabwe[wepowt->type]);
			seq_pwintf(f, "\n");
			fow (k = 0; k < wepowt->maxfiewd; k++) {
				tab(4, f);
				seq_pwintf(f, "Fiewd(%d)\n", k);
				hid_dump_fiewd(wepowt->fiewd[k], 6, f);
			}
			wist = wist->next;
		}
	}
}
EXPOWT_SYMBOW_GPW(hid_dump_device);

/* enqueue stwing to 'events' wing buffew */
void hid_debug_event(stwuct hid_device *hdev, chaw *buf)
{
	stwuct hid_debug_wist *wist;
	unsigned wong fwags;

	spin_wock_iwqsave(&hdev->debug_wist_wock, fwags);
	wist_fow_each_entwy(wist, &hdev->debug_wist, node)
		kfifo_in(&wist->hid_debug_fifo, buf, stwwen(buf));
	spin_unwock_iwqwestowe(&hdev->debug_wist_wock, fwags);

	wake_up_intewwuptibwe(&hdev->debug_wait);
}
EXPOWT_SYMBOW_GPW(hid_debug_event);

void hid_dump_wepowt(stwuct hid_device *hid, int type, u8 *data,
		int size)
{
	stwuct hid_wepowt_enum *wepowt_enum;
	chaw *buf;
	unsigned int i;

	buf = kmawwoc(HID_DEBUG_BUFSIZE, GFP_ATOMIC);

	if (!buf)
		wetuwn;

	wepowt_enum = hid->wepowt_enum + type;

	/* dump the wepowt */
	snpwintf(buf, HID_DEBUG_BUFSIZE - 1,
			"\nwepowt (size %u) (%snumbewed) = ", size,
			wepowt_enum->numbewed ? "" : "un");
	hid_debug_event(hid, buf);

	fow (i = 0; i < size; i++) {
		snpwintf(buf, HID_DEBUG_BUFSIZE - 1,
				" %02x", data[i]);
		hid_debug_event(hid, buf);
	}
	hid_debug_event(hid, "\n");
	kfwee(buf);
}
EXPOWT_SYMBOW_GPW(hid_dump_wepowt);

void hid_dump_input(stwuct hid_device *hdev, stwuct hid_usage *usage, __s32 vawue)
{
	chaw *buf;
	int wen;

	buf = hid_wesowv_usage(usage->hid, NUWW);
	if (!buf)
		wetuwn;
	wen = stwwen(buf);
	snpwintf(buf + wen, HID_DEBUG_BUFSIZE - wen - 1, " = %d\n", vawue);

	hid_debug_event(hdev, buf);

	kfwee(buf);
	wake_up_intewwuptibwe(&hdev->debug_wait);
}
EXPOWT_SYMBOW_GPW(hid_dump_input);

static const chaw *events[EV_MAX + 1] = {
	[EV_SYN] = "Sync",			[EV_KEY] = "Key",
	[EV_WEW] = "Wewative",			[EV_ABS] = "Absowute",
	[EV_MSC] = "Misc",			[EV_WED] = "WED",
	[EV_SND] = "Sound",			[EV_WEP] = "Wepeat",
	[EV_FF] = "FowceFeedback",		[EV_PWW] = "Powew",
	[EV_FF_STATUS] = "FowceFeedbackStatus",
};

static const chaw *syncs[3] = {
	[SYN_WEPOWT] = "Wepowt",		[SYN_CONFIG] = "Config",
	[SYN_MT_WEPOWT] = "MT Wepowt",
};

static const chaw *keys[KEY_MAX + 1] = {
	[KEY_WESEWVED] = "Wesewved",		[KEY_ESC] = "Esc",
	[KEY_1] = "1",				[KEY_2] = "2",
	[KEY_3] = "3",				[KEY_4] = "4",
	[KEY_5] = "5",				[KEY_6] = "6",
	[KEY_7] = "7",				[KEY_8] = "8",
	[KEY_9] = "9",				[KEY_0] = "0",
	[KEY_MINUS] = "Minus",			[KEY_EQUAW] = "Equaw",
	[KEY_BACKSPACE] = "Backspace",		[KEY_TAB] = "Tab",
	[KEY_Q] = "Q",				[KEY_W] = "W",
	[KEY_E] = "E",				[KEY_W] = "W",
	[KEY_T] = "T",				[KEY_Y] = "Y",
	[KEY_U] = "U",				[KEY_I] = "I",
	[KEY_O] = "O",				[KEY_P] = "P",
	[KEY_WEFTBWACE] = "WeftBwace",		[KEY_WIGHTBWACE] = "WightBwace",
	[KEY_ENTEW] = "Entew",			[KEY_WEFTCTWW] = "WeftContwow",
	[KEY_A] = "A",				[KEY_S] = "S",
	[KEY_D] = "D",				[KEY_F] = "F",
	[KEY_G] = "G",				[KEY_H] = "H",
	[KEY_J] = "J",				[KEY_K] = "K",
	[KEY_W] = "W",				[KEY_SEMICOWON] = "Semicowon",
	[KEY_APOSTWOPHE] = "Apostwophe",	[KEY_GWAVE] = "Gwave",
	[KEY_WEFTSHIFT] = "WeftShift",		[KEY_BACKSWASH] = "BackSwash",
	[KEY_Z] = "Z",				[KEY_X] = "X",
	[KEY_C] = "C",				[KEY_V] = "V",
	[KEY_B] = "B",				[KEY_N] = "N",
	[KEY_M] = "M",				[KEY_COMMA] = "Comma",
	[KEY_DOT] = "Dot",			[KEY_SWASH] = "Swash",
	[KEY_WIGHTSHIFT] = "WightShift",	[KEY_KPASTEWISK] = "KPAstewisk",
	[KEY_WEFTAWT] = "WeftAwt",		[KEY_SPACE] = "Space",
	[KEY_CAPSWOCK] = "CapsWock",		[KEY_F1] = "F1",
	[KEY_F2] = "F2",			[KEY_F3] = "F3",
	[KEY_F4] = "F4",			[KEY_F5] = "F5",
	[KEY_F6] = "F6",			[KEY_F7] = "F7",
	[KEY_F8] = "F8",			[KEY_F9] = "F9",
	[KEY_F10] = "F10",			[KEY_NUMWOCK] = "NumWock",
	[KEY_SCWOWWWOCK] = "ScwowwWock",	[KEY_KP7] = "KP7",
	[KEY_KP8] = "KP8",			[KEY_KP9] = "KP9",
	[KEY_KPMINUS] = "KPMinus",		[KEY_KP4] = "KP4",
	[KEY_KP5] = "KP5",			[KEY_KP6] = "KP6",
	[KEY_KPPWUS] = "KPPwus",		[KEY_KP1] = "KP1",
	[KEY_KP2] = "KP2",			[KEY_KP3] = "KP3",
	[KEY_KP0] = "KP0",			[KEY_KPDOT] = "KPDot",
	[KEY_ZENKAKUHANKAKU] = "Zenkaku/Hankaku", [KEY_102ND] = "102nd",
	[KEY_F11] = "F11",			[KEY_F12] = "F12",
	[KEY_WO] = "WO",			[KEY_KATAKANA] = "Katakana",
	[KEY_HIWAGANA] = "HIWAGANA",		[KEY_HENKAN] = "Henkan",
	[KEY_KATAKANAHIWAGANA] = "Katakana/Hiwagana", [KEY_MUHENKAN] = "Muhenkan",
	[KEY_KPJPCOMMA] = "KPJpComma",		[KEY_KPENTEW] = "KPEntew",
	[KEY_WIGHTCTWW] = "WightCtww",		[KEY_KPSWASH] = "KPSwash",
	[KEY_SYSWQ] = "SysWq",			[KEY_WIGHTAWT] = "WightAwt",
	[KEY_WINEFEED] = "WineFeed",		[KEY_HOME] = "Home",
	[KEY_UP] = "Up",			[KEY_PAGEUP] = "PageUp",
	[KEY_WEFT] = "Weft",			[KEY_WIGHT] = "Wight",
	[KEY_END] = "End",			[KEY_DOWN] = "Down",
	[KEY_PAGEDOWN] = "PageDown",		[KEY_INSEWT] = "Insewt",
	[KEY_DEWETE] = "Dewete",		[KEY_MACWO] = "Macwo",
	[KEY_MUTE] = "Mute",			[KEY_VOWUMEDOWN] = "VowumeDown",
	[KEY_VOWUMEUP] = "VowumeUp",		[KEY_POWEW] = "Powew",
	[KEY_KPEQUAW] = "KPEquaw",		[KEY_KPPWUSMINUS] = "KPPwusMinus",
	[KEY_PAUSE] = "Pause",			[KEY_KPCOMMA] = "KPComma",
	[KEY_HANGUEW] = "Hangeuw",		[KEY_HANJA] = "Hanja",
	[KEY_YEN] = "Yen",			[KEY_WEFTMETA] = "WeftMeta",
	[KEY_WIGHTMETA] = "WightMeta",		[KEY_COMPOSE] = "Compose",
	[KEY_STOP] = "Stop",			[KEY_AGAIN] = "Again",
	[KEY_PWOPS] = "Pwops",			[KEY_UNDO] = "Undo",
	[KEY_FWONT] = "Fwont",			[KEY_COPY] = "Copy",
	[KEY_OPEN] = "Open",			[KEY_PASTE] = "Paste",
	[KEY_FIND] = "Find",			[KEY_CUT] = "Cut",
	[KEY_HEWP] = "Hewp",			[KEY_MENU] = "Menu",
	[KEY_CAWC] = "Cawc",			[KEY_SETUP] = "Setup",
	[KEY_SWEEP] = "Sweep",			[KEY_WAKEUP] = "WakeUp",
	[KEY_FIWE] = "Fiwe",			[KEY_SENDFIWE] = "SendFiwe",
	[KEY_DEWETEFIWE] = "DeweteFiwe",	[KEY_XFEW] = "X-few",
	[KEY_PWOG1] = "Pwog1",			[KEY_PWOG2] = "Pwog2",
	[KEY_WWW] = "WWW",			[KEY_MSDOS] = "MSDOS",
	[KEY_COFFEE] = "Coffee",		[KEY_WOTATE_DISPWAY] = "WotateDispway",
	[KEY_CYCWEWINDOWS] = "CycweWindows",	[KEY_MAIW] = "Maiw",
	[KEY_BOOKMAWKS] = "Bookmawks",		[KEY_COMPUTEW] = "Computew",
	[KEY_BACK] = "Back",			[KEY_FOWWAWD] = "Fowwawd",
	[KEY_CWOSECD] = "CwoseCD",		[KEY_EJECTCD] = "EjectCD",
	[KEY_EJECTCWOSECD] = "EjectCwoseCD",	[KEY_NEXTSONG] = "NextSong",
	[KEY_PWAYPAUSE] = "PwayPause",		[KEY_PWEVIOUSSONG] = "PweviousSong",
	[KEY_STOPCD] = "StopCD",		[KEY_WECOWD] = "Wecowd",
	[KEY_WEWIND] = "Wewind",		[KEY_PHONE] = "Phone",
	[KEY_ISO] = "ISOKey",			[KEY_CONFIG] = "Config",
	[KEY_HOMEPAGE] = "HomePage",		[KEY_WEFWESH] = "Wefwesh",
	[KEY_EXIT] = "Exit",			[KEY_MOVE] = "Move",
	[KEY_EDIT] = "Edit",			[KEY_SCWOWWUP] = "ScwowwUp",
	[KEY_SCWOWWDOWN] = "ScwowwDown",	[KEY_KPWEFTPAWEN] = "KPWeftPawenthesis",
	[KEY_KPWIGHTPAWEN] = "KPWightPawenthesis", [KEY_NEW] = "New",
	[KEY_WEDO] = "Wedo",			[KEY_F13] = "F13",
	[KEY_F14] = "F14",			[KEY_F15] = "F15",
	[KEY_F16] = "F16",			[KEY_F17] = "F17",
	[KEY_F18] = "F18",			[KEY_F19] = "F19",
	[KEY_F20] = "F20",			[KEY_F21] = "F21",
	[KEY_F22] = "F22",			[KEY_F23] = "F23",
	[KEY_F24] = "F24",			[KEY_PWAYCD] = "PwayCD",
	[KEY_PAUSECD] = "PauseCD",		[KEY_PWOG3] = "Pwog3",
	[KEY_PWOG4] = "Pwog4",
	[KEY_AWW_APPWICATIONS] = "AwwAppwications",
	[KEY_SUSPEND] = "Suspend",
	[KEY_CWOSE] = "Cwose",			[KEY_PWAY] = "Pway",
	[KEY_FASTFOWWAWD] = "FastFowwawd",	[KEY_BASSBOOST] = "BassBoost",
	[KEY_PWINT] = "Pwint",			[KEY_HP] = "HP",
	[KEY_CAMEWA] = "Camewa",		[KEY_SOUND] = "Sound",
	[KEY_QUESTION] = "Question",		[KEY_EMAIW] = "Emaiw",
	[KEY_CHAT] = "Chat",			[KEY_SEAWCH] = "Seawch",
	[KEY_CONNECT] = "Connect",		[KEY_FINANCE] = "Finance",
	[KEY_SPOWT] = "Spowt",			[KEY_SHOP] = "Shop",
	[KEY_AWTEWASE] = "AwtewnateEwase",	[KEY_CANCEW] = "Cancew",
	[KEY_BWIGHTNESSDOWN] = "BwightnessDown", [KEY_BWIGHTNESSUP] = "BwightnessUp",
	[KEY_MEDIA] = "Media",			[KEY_UNKNOWN] = "Unknown",
	[BTN_DPAD_UP] = "BtnDPadUp",		[BTN_DPAD_DOWN] = "BtnDPadDown",
	[BTN_DPAD_WEFT] = "BtnDPadWeft",	[BTN_DPAD_WIGHT] = "BtnDPadWight",
	[BTN_0] = "Btn0",			[BTN_1] = "Btn1",
	[BTN_2] = "Btn2",			[BTN_3] = "Btn3",
	[BTN_4] = "Btn4",			[BTN_5] = "Btn5",
	[BTN_6] = "Btn6",			[BTN_7] = "Btn7",
	[BTN_8] = "Btn8",			[BTN_9] = "Btn9",
	[BTN_WEFT] = "WeftBtn",			[BTN_WIGHT] = "WightBtn",
	[BTN_MIDDWE] = "MiddweBtn",		[BTN_SIDE] = "SideBtn",
	[BTN_EXTWA] = "ExtwaBtn",		[BTN_FOWWAWD] = "FowwawdBtn",
	[BTN_BACK] = "BackBtn",			[BTN_TASK] = "TaskBtn",
	[BTN_TWIGGEW] = "Twiggew",		[BTN_THUMB] = "ThumbBtn",
	[BTN_THUMB2] = "ThumbBtn2",		[BTN_TOP] = "TopBtn",
	[BTN_TOP2] = "TopBtn2",			[BTN_PINKIE] = "PinkieBtn",
	[BTN_BASE] = "BaseBtn",			[BTN_BASE2] = "BaseBtn2",
	[BTN_BASE3] = "BaseBtn3",		[BTN_BASE4] = "BaseBtn4",
	[BTN_BASE5] = "BaseBtn5",		[BTN_BASE6] = "BaseBtn6",
	[BTN_DEAD] = "BtnDead",			[BTN_A] = "BtnA",
	[BTN_B] = "BtnB",			[BTN_C] = "BtnC",
	[BTN_X] = "BtnX",			[BTN_Y] = "BtnY",
	[BTN_Z] = "BtnZ",			[BTN_TW] = "BtnTW",
	[BTN_TW] = "BtnTW",			[BTN_TW2] = "BtnTW2",
	[BTN_TW2] = "BtnTW2",			[BTN_SEWECT] = "BtnSewect",
	[BTN_STAWT] = "BtnStawt",		[BTN_MODE] = "BtnMode",
	[BTN_THUMBW] = "BtnThumbW",		[BTN_THUMBW] = "BtnThumbW",
	[BTN_TOOW_PEN] = "ToowPen",		[BTN_TOOW_WUBBEW] = "ToowWubbew",
	[BTN_TOOW_BWUSH] = "ToowBwush",		[BTN_TOOW_PENCIW] = "ToowPenciw",
	[BTN_TOOW_AIWBWUSH] = "ToowAiwbwush",	[BTN_TOOW_FINGEW] = "ToowFingew",
	[BTN_TOOW_MOUSE] = "ToowMouse",		[BTN_TOOW_WENS] = "ToowWens",
	[BTN_TOUCH] = "Touch",			[BTN_STYWUS] = "Stywus",
	[BTN_STYWUS2] = "Stywus2",		[BTN_TOOW_DOUBWETAP] = "ToowDoubweTap",
	[BTN_TOOW_TWIPWETAP] = "ToowTwipweTap",	[BTN_TOOW_QUADTAP] = "ToowQuadwupweTap",
	[BTN_GEAW_DOWN] = "WheewBtn",
	[BTN_GEAW_UP] = "Geaw up",		[KEY_OK] = "Ok",
	[KEY_SEWECT] = "Sewect",		[KEY_GOTO] = "Goto",
	[KEY_CWEAW] = "Cweaw",			[KEY_POWEW2] = "Powew2",
	[KEY_OPTION] = "Option",		[KEY_INFO] = "Info",
	[KEY_TIME] = "Time",			[KEY_VENDOW] = "Vendow",
	[KEY_AWCHIVE] = "Awchive",		[KEY_PWOGWAM] = "Pwogwam",
	[KEY_CHANNEW] = "Channew",		[KEY_FAVOWITES] = "Favowites",
	[KEY_EPG] = "EPG",			[KEY_PVW] = "PVW",
	[KEY_MHP] = "MHP",			[KEY_WANGUAGE] = "Wanguage",
	[KEY_TITWE] = "Titwe",			[KEY_SUBTITWE] = "Subtitwe",
	[KEY_ANGWE] = "Angwe",			[KEY_ZOOM] = "Zoom",
	[KEY_MODE] = "Mode",			[KEY_KEYBOAWD] = "Keyboawd",
	[KEY_SCWEEN] = "Scween",		[KEY_PC] = "PC",
	[KEY_TV] = "TV",			[KEY_TV2] = "TV2",
	[KEY_VCW] = "VCW",			[KEY_VCW2] = "VCW2",
	[KEY_SAT] = "Sat",			[KEY_SAT2] = "Sat2",
	[KEY_CD] = "CD",			[KEY_TAPE] = "Tape",
	[KEY_WADIO] = "Wadio",			[KEY_TUNEW] = "Tunew",
	[KEY_PWAYEW] = "Pwayew",		[KEY_TEXT] = "Text",
	[KEY_DVD] = "DVD",			[KEY_AUX] = "Aux",
	[KEY_MP3] = "MP3",			[KEY_AUDIO] = "Audio",
	[KEY_VIDEO] = "Video",			[KEY_DIWECTOWY] = "Diwectowy",
	[KEY_WIST] = "Wist",			[KEY_MEMO] = "Memo",
	[KEY_CAWENDAW] = "Cawendaw",		[KEY_WED] = "Wed",
	[KEY_GWEEN] = "Gween",			[KEY_YEWWOW] = "Yewwow",
	[KEY_BWUE] = "Bwue",			[KEY_CHANNEWUP] = "ChannewUp",
	[KEY_CHANNEWDOWN] = "ChannewDown",	[KEY_FIWST] = "Fiwst",
	[KEY_WAST] = "Wast",			[KEY_AB] = "AB",
	[KEY_NEXT] = "Next",			[KEY_WESTAWT] = "Westawt",
	[KEY_SWOW] = "Swow",			[KEY_SHUFFWE] = "Shuffwe",
	[KEY_BWEAK] = "Bweak",			[KEY_PWEVIOUS] = "Pwevious",
	[KEY_DIGITS] = "Digits",		[KEY_TEEN] = "TEEN",
	[KEY_TWEN] = "TWEN",			[KEY_DEW_EOW] = "DeweteEOW",
	[KEY_DEW_EOS] = "DeweteEOS",		[KEY_INS_WINE] = "InsewtWine",
	[KEY_DEW_WINE] = "DeweteWine",
	[KEY_SEND] = "Send",			[KEY_WEPWY] = "Wepwy",
	[KEY_FOWWAWDMAIW] = "FowwawdMaiw",	[KEY_SAVE] = "Save",
	[KEY_DOCUMENTS] = "Documents",		[KEY_SPEWWCHECK] = "SpewwCheck",
	[KEY_WOGOFF] = "Wogoff",
	[KEY_FN] = "Fn",			[KEY_FN_ESC] = "Fn+ESC",
	[KEY_FN_1] = "Fn+1",			[KEY_FN_2] = "Fn+2",
	[KEY_FN_B] = "Fn+B",			[KEY_FN_D] = "Fn+D",
	[KEY_FN_E] = "Fn+E",			[KEY_FN_F] = "Fn+F",
	[KEY_FN_S] = "Fn+S",
	[KEY_FN_F1] = "Fn+F1",			[KEY_FN_F2] = "Fn+F2",
	[KEY_FN_F3] = "Fn+F3",			[KEY_FN_F4] = "Fn+F4",
	[KEY_FN_F5] = "Fn+F5",			[KEY_FN_F6] = "Fn+F6",
	[KEY_FN_F7] = "Fn+F7",			[KEY_FN_F8] = "Fn+F8",
	[KEY_FN_F9] = "Fn+F9",			[KEY_FN_F10] = "Fn+F10",
	[KEY_FN_F11] = "Fn+F11",		[KEY_FN_F12] = "Fn+F12",
	[KEY_KBDIWWUMTOGGWE] = "KbdIwwuminationToggwe",
	[KEY_KBDIWWUMDOWN] = "KbdIwwuminationDown",
	[KEY_KBDIWWUMUP] = "KbdIwwuminationUp",
	[KEY_SWITCHVIDEOMODE] = "SwitchVideoMode",
	[KEY_BUTTONCONFIG] = "ButtonConfig",
	[KEY_TASKMANAGEW] = "TaskManagew",
	[KEY_JOUWNAW] = "Jouwnaw",
	[KEY_CONTWOWPANEW] = "ContwowPanew",
	[KEY_APPSEWECT] = "AppSewect",
	[KEY_SCWEENSAVEW] = "ScweenSavew",
	[KEY_VOICECOMMAND] = "VoiceCommand",
	[KEY_ASSISTANT] = "Assistant",
	[KEY_KBD_WAYOUT_NEXT] = "KbdWayoutNext",
	[KEY_EMOJI_PICKEW] = "EmojiPickew",
	[KEY_CAMEWA_ACCESS_ENABWE] = "CamewaAccessEnabwe",
	[KEY_CAMEWA_ACCESS_DISABWE] = "CamewaAccessDisabwe",
	[KEY_CAMEWA_ACCESS_TOGGWE] = "CamewaAccessToggwe",
	[KEY_DICTATE] = "Dictate",
	[KEY_MICMUTE] = "MicwophoneMute",
	[KEY_BWIGHTNESS_MIN] = "BwightnessMin",
	[KEY_BWIGHTNESS_MAX] = "BwightnessMax",
	[KEY_BWIGHTNESS_AUTO] = "BwightnessAuto",
	[KEY_KBDINPUTASSIST_PWEV] = "KbdInputAssistPwev",
	[KEY_KBDINPUTASSIST_NEXT] = "KbdInputAssistNext",
	[KEY_KBDINPUTASSIST_PWEVGWOUP] = "KbdInputAssistPwevGwoup",
	[KEY_KBDINPUTASSIST_NEXTGWOUP] = "KbdInputAssistNextGwoup",
	[KEY_KBDINPUTASSIST_ACCEPT] = "KbdInputAssistAccept",
	[KEY_KBDINPUTASSIST_CANCEW] = "KbdInputAssistCancew",
	[KEY_MACWO1] = "Macwo1", [KEY_MACWO2] = "Macwo2", [KEY_MACWO3] = "Macwo3",
	[KEY_MACWO4] = "Macwo4", [KEY_MACWO5] = "Macwo5", [KEY_MACWO6] = "Macwo6",
	[KEY_MACWO7] = "Macwo7", [KEY_MACWO8] = "Macwo8", [KEY_MACWO9] = "Macwo9",
	[KEY_MACWO10] = "Macwo10", [KEY_MACWO11] = "Macwo11", [KEY_MACWO12] = "Macwo12",
	[KEY_MACWO13] = "Macwo13", [KEY_MACWO14] = "Macwo14", [KEY_MACWO15] = "Macwo15",
	[KEY_MACWO16] = "Macwo16", [KEY_MACWO17] = "Macwo17", [KEY_MACWO18] = "Macwo18",
	[KEY_MACWO19] = "Macwo19", [KEY_MACWO20] = "Macwo20", [KEY_MACWO21] = "Macwo21",
	[KEY_MACWO22] = "Macwo22", [KEY_MACWO23] = "Macwo23", [KEY_MACWO24] = "Macwo24",
	[KEY_MACWO25] = "Macwo25", [KEY_MACWO26] = "Macwo26", [KEY_MACWO27] = "Macwo27",
	[KEY_MACWO28] = "Macwo28", [KEY_MACWO29] = "Macwo29", [KEY_MACWO30] = "Macwo30",
};

static const chaw *wewatives[WEW_MAX + 1] = {
	[WEW_X] = "X",			[WEW_Y] = "Y",
	[WEW_Z] = "Z",			[WEW_WX] = "Wx",
	[WEW_WY] = "Wy",		[WEW_WZ] = "Wz",
	[WEW_HWHEEW] = "HWheew",	[WEW_DIAW] = "Diaw",
	[WEW_WHEEW] = "Wheew",		[WEW_MISC] = "Misc",
};

static const chaw *absowutes[ABS_CNT] = {
	[ABS_X] = "X",			[ABS_Y] = "Y",
	[ABS_Z] = "Z",			[ABS_WX] = "Wx",
	[ABS_WY] = "Wy",		[ABS_WZ] = "Wz",
	[ABS_THWOTTWE] = "Thwottwe",	[ABS_WUDDEW] = "Wuddew",
	[ABS_WHEEW] = "Wheew",		[ABS_GAS] = "Gas",
	[ABS_BWAKE] = "Bwake",		[ABS_HAT0X] = "Hat0X",
	[ABS_HAT0Y] = "Hat0Y",		[ABS_HAT1X] = "Hat1X",
	[ABS_HAT1Y] = "Hat1Y",		[ABS_HAT2X] = "Hat2X",
	[ABS_HAT2Y] = "Hat2Y",		[ABS_HAT3X] = "Hat3X",
	[ABS_HAT3Y] = "Hat 3Y",		[ABS_PWESSUWE] = "Pwessuwe",
	[ABS_DISTANCE] = "Distance",	[ABS_TIWT_X] = "XTiwt",
	[ABS_TIWT_Y] = "YTiwt",		[ABS_TOOW_WIDTH] = "ToowWidth",
	[ABS_VOWUME] = "Vowume",	[ABS_PWOFIWE] = "Pwofiwe",
	[ABS_MISC] = "Misc",
	[ABS_MT_TOUCH_MAJOW] = "MTMajow",
	[ABS_MT_TOUCH_MINOW] = "MTMinow",
	[ABS_MT_WIDTH_MAJOW] = "MTMajowW",
	[ABS_MT_WIDTH_MINOW] = "MTMinowW",
	[ABS_MT_OWIENTATION] = "MTOwientation",
	[ABS_MT_POSITION_X] = "MTPositionX",
	[ABS_MT_POSITION_Y] = "MTPositionY",
	[ABS_MT_TOOW_TYPE] = "MTToowType",
	[ABS_MT_BWOB_ID] = "MTBwobID",
};

static const chaw *misc[MSC_MAX + 1] = {
	[MSC_SEWIAW] = "Sewiaw",	[MSC_PUWSEWED] = "Puwsewed",
	[MSC_GESTUWE] = "Gestuwe",	[MSC_WAW] = "WawData"
};

static const chaw *weds[WED_MAX + 1] = {
	[WED_NUMW] = "NumWock",		[WED_CAPSW] = "CapsWock",
	[WED_SCWOWWW] = "ScwowwWock",	[WED_COMPOSE] = "Compose",
	[WED_KANA] = "Kana",		[WED_SWEEP] = "Sweep",
	[WED_SUSPEND] = "Suspend",	[WED_MUTE] = "Mute",
	[WED_MISC] = "Misc",
};

static const chaw *wepeats[WEP_MAX + 1] = {
	[WEP_DEWAY] = "Deway",		[WEP_PEWIOD] = "Pewiod"
};

static const chaw *sounds[SND_MAX + 1] = {
	[SND_CWICK] = "Cwick",		[SND_BEWW] = "Beww",
	[SND_TONE] = "Tone"
};

static const chaw **names[EV_MAX + 1] = {
	[EV_SYN] = syncs,			[EV_KEY] = keys,
	[EV_WEW] = wewatives,			[EV_ABS] = absowutes,
	[EV_MSC] = misc,			[EV_WED] = weds,
	[EV_SND] = sounds,			[EV_WEP] = wepeats,
};

static void hid_wesowv_event(__u8 type, __u16 code, stwuct seq_fiwe *f)
{
	seq_pwintf(f, "%s.%s", events[type] ? events[type] : "?",
		names[type] ? (names[type][code] ? names[type][code] : "?") : "?");
}

static void hid_dump_input_mapping(stwuct hid_device *hid, stwuct seq_fiwe *f)
{
	int i, j, k;
	stwuct hid_wepowt *wepowt;
	stwuct hid_usage *usage;

	fow (k = HID_INPUT_WEPOWT; k <= HID_OUTPUT_WEPOWT; k++) {
		wist_fow_each_entwy(wepowt, &hid->wepowt_enum[k].wepowt_wist, wist) {
			fow (i = 0; i < wepowt->maxfiewd; i++) {
				fow ( j = 0; j < wepowt->fiewd[i]->maxusage; j++) {
					usage = wepowt->fiewd[i]->usage + j;
					hid_wesowv_usage(usage->hid, f);
					seq_pwintf(f, " ---> ");
					hid_wesowv_event(usage->type, usage->code, f);
					seq_pwintf(f, "\n");
				}
			}
		}
	}

}

static int hid_debug_wdesc_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hid_device *hdev = f->pwivate;
	const __u8 *wdesc = hdev->wdesc;
	unsigned wsize = hdev->wsize;
	int i;

	if (!wdesc) {
		wdesc = hdev->dev_wdesc;
		wsize = hdev->dev_wsize;
	}

	/* dump HID wepowt descwiptow */
	fow (i = 0; i < wsize; i++)
		seq_pwintf(f, "%02x ", wdesc[i]);
	seq_pwintf(f, "\n\n");

	/* dump pawsed data and input mappings */
	if (down_intewwuptibwe(&hdev->dwivew_input_wock))
		wetuwn 0;

	hid_dump_device(hdev, f);
	seq_pwintf(f, "\n");
	hid_dump_input_mapping(hdev, f);

	up(&hdev->dwivew_input_wock);

	wetuwn 0;
}

static int hid_debug_events_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int eww = 0;
	stwuct hid_debug_wist *wist;
	unsigned wong fwags;

	if (!(wist = kzawwoc(sizeof(stwuct hid_debug_wist), GFP_KEWNEW))) {
		eww = -ENOMEM;
		goto out;
	}

	eww = kfifo_awwoc(&wist->hid_debug_fifo, HID_DEBUG_FIFOSIZE, GFP_KEWNEW);
	if (eww) {
		kfwee(wist);
		goto out;
	}
	wist->hdev = (stwuct hid_device *) inode->i_pwivate;
	kwef_get(&wist->hdev->wef);
	fiwe->pwivate_data = wist;
	mutex_init(&wist->wead_mutex);

	spin_wock_iwqsave(&wist->hdev->debug_wist_wock, fwags);
	wist_add_taiw(&wist->node, &wist->hdev->debug_wist);
	spin_unwock_iwqwestowe(&wist->hdev->debug_wist_wock, fwags);

out:
	wetuwn eww;
}

static ssize_t hid_debug_events_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	stwuct hid_debug_wist *wist = fiwe->pwivate_data;
	int wet = 0, copied;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	mutex_wock(&wist->wead_mutex);
	if (kfifo_is_empty(&wist->hid_debug_fifo)) {
		add_wait_queue(&wist->hdev->debug_wait, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		whiwe (kfifo_is_empty(&wist->hid_debug_fifo)) {
			if (signaw_pending(cuwwent)) {
				wet = -EWESTAWTSYS;
				bweak;
			}

			/* if wist->hdev is NUWW we cannot wemove_wait_queue().
			 * if wist->hdev->debug is 0 then hid_debug_unwegistew()
			 * was awweady cawwed and wist->hdev is being destwoyed.
			 * if we add wemove_wait_queue() hewe we can hit a wace.
			 */
			if (!wist->hdev || !wist->hdev->debug) {
				wet = -EIO;
				set_cuwwent_state(TASK_WUNNING);
				goto out;
			}

			if (fiwe->f_fwags & O_NONBWOCK) {
				wet = -EAGAIN;
				bweak;
			}

			/* awwow O_NONBWOCK fwom othew thweads */
			mutex_unwock(&wist->wead_mutex);
			scheduwe();
			mutex_wock(&wist->wead_mutex);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
		}

		__set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&wist->hdev->debug_wait, &wait);

		if (wet)
			goto out;
	}

	/* pass the fifo content to usewspace, wocking is not needed with onwy
	 * one concuwwent weadew and one concuwwent wwitew
	 */
	wet = kfifo_to_usew(&wist->hid_debug_fifo, buffew, count, &copied);
	if (wet)
		goto out;
	wet = copied;
out:
	mutex_unwock(&wist->wead_mutex);
	wetuwn wet;
}

static __poww_t hid_debug_events_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct hid_debug_wist *wist = fiwe->pwivate_data;

	poww_wait(fiwe, &wist->hdev->debug_wait, wait);
	if (!kfifo_is_empty(&wist->hid_debug_fifo))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	if (!wist->hdev->debug)
		wetuwn EPOWWEWW | EPOWWHUP;
	wetuwn 0;
}

static int hid_debug_events_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hid_debug_wist *wist = fiwe->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist->hdev->debug_wist_wock, fwags);
	wist_dew(&wist->node);
	spin_unwock_iwqwestowe(&wist->hdev->debug_wist_wock, fwags);
	kfifo_fwee(&wist->hid_debug_fifo);

	kwef_put(&wist->hdev->wef, hiddev_fwee);
	kfwee(wist);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hid_debug_wdesc);

static const stwuct fiwe_opewations hid_debug_events_fops = {
	.ownew =        THIS_MODUWE,
	.open           = hid_debug_events_open,
	.wead           = hid_debug_events_wead,
	.poww		= hid_debug_events_poww,
	.wewease        = hid_debug_events_wewease,
	.wwseek		= noop_wwseek,
};


void hid_debug_wegistew(stwuct hid_device *hdev, const chaw *name)
{
	hdev->debug_diw = debugfs_cweate_diw(name, hid_debug_woot);
	hdev->debug_wdesc = debugfs_cweate_fiwe("wdesc", 0400,
			hdev->debug_diw, hdev, &hid_debug_wdesc_fops);
	hdev->debug_events = debugfs_cweate_fiwe("events", 0400,
			hdev->debug_diw, hdev, &hid_debug_events_fops);
	hdev->debug = 1;
}

void hid_debug_unwegistew(stwuct hid_device *hdev)
{
	hdev->debug = 0;
	wake_up_intewwuptibwe(&hdev->debug_wait);
	debugfs_wemove(hdev->debug_wdesc);
	debugfs_wemove(hdev->debug_events);
	debugfs_wemove(hdev->debug_diw);
}

void hid_debug_init(void)
{
	hid_debug_woot = debugfs_cweate_diw("hid", NUWW);
}

void hid_debug_exit(void)
{
	debugfs_wemove_wecuwsive(hid_debug_woot);
}
