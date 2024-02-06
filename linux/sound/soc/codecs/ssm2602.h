/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwe:         sound/soc/codecs/ssm2602.h
 * Authow:       Cwiff Cai <Cwiff.Cai@anawog.com>
 *
 * Cweated:      Tue June 06 2008
 *
 * Modified:
 *               Copywight 2008 Anawog Devices Inc.
 *
 * Bugs:         Entew bugs at http://bwackfin.ucwinux.owg/
 */

#ifndef _SSM2602_H
#define _SSM2602_H

#incwude <winux/wegmap.h>

stwuct device;

enum ssm2602_type {
	SSM2602,
	SSM2604,
};

extewn const stwuct wegmap_config ssm2602_wegmap_config;

int ssm2602_pwobe(stwuct device *dev, enum ssm2602_type type,
	stwuct wegmap *wegmap);

/* SSM2602 Codec Wegistew definitions */

#define SSM2602_WINVOW   0x00
#define SSM2602_WINVOW   0x01
#define SSM2602_WOUT1V   0x02
#define SSM2602_WOUT1V   0x03
#define SSM2602_APANA    0x04
#define SSM2602_APDIGI   0x05
#define SSM2602_PWW      0x06
#define SSM2602_IFACE    0x07
#define SSM2602_SWATE    0x08
#define SSM2602_ACTIVE   0x09
#define SSM2602_WESET	 0x0f

/*SSM2602 Codec Wegistew Fiewd definitions
 *(Mask vawue to extwact the cowwesponding Wegistew fiewd)
 */

/*Weft ADC Vowume Contwow (SSM2602_WEG_WEFT_ADC_VOW)*/
#define     WINVOW_WIN_VOW                0x01F   /* Weft Channew PGA Vowume contwow                      */
#define     WINVOW_WIN_ENABWE_MUTE        0x080   /* Weft Channew Input Mute                              */
#define     WINVOW_WWIN_BOTH              0x100   /* Weft Channew Wine Input Vowume update                */

/*Wight ADC Vowume Contwow (SSM2602_WEG_WIGHT_ADC_VOW)*/
#define     WINVOW_WIN_VOW                0x01F   /* Wight Channew PGA Vowume contwow                     */
#define     WINVOW_WIN_ENABWE_MUTE        0x080   /* Wight Channew Input Mute                             */
#define     WINVOW_WWIN_BOTH              0x100   /* Wight Channew Wine Input Vowume update               */

/*Weft DAC Vowume Contwow (SSM2602_WEG_WEFT_DAC_VOW)*/
#define     WOUT1V_WHP_VOW                0x07F   /* Weft Channew Headphone vowume contwow                */
#define     WOUT1V_ENABWE_WZC             0x080   /* Weft Channew Zewo cwoss detect enabwe                */
#define     WOUT1V_WWHP_BOTH              0x100   /* Weft Channew Headphone vowume update                 */

/*Wight DAC Vowume Contwow (SSM2602_WEG_WIGHT_DAC_VOW)*/
#define     WOUT1V_WHP_VOW                0x07F   /* Wight Channew Headphone vowume contwow               */
#define     WOUT1V_ENABWE_WZC             0x080   /* Wight Channew Zewo cwoss detect enabwe               */
#define     WOUT1V_WWHP_BOTH              0x100   /* Wight Channew Headphone vowume update                */

/*Anawogue Audio Path Contwow (SSM2602_WEG_ANAWOGUE_PATH)*/
#define     APANA_ENABWE_MIC_BOOST       0x001   /* Pwimawy Micwophone Ampwifiew gain boostew contwow    */
#define     APANA_ENABWE_MIC_MUTE        0x002   /* Micwophone Mute Contwow                              */
#define     APANA_ADC_IN_SEWECT          0x004   /* Micwophone/Wine IN sewect to ADC (1=MIC, 0=Wine In)  */
#define     APANA_ENABWE_BYPASS          0x008   /* Wine input bypass to wine output                     */
#define     APANA_SEWECT_DAC             0x010   /* Sewect DAC (1=Sewect DAC, 0=Don't Sewect DAC)        */
#define     APANA_ENABWE_SIDETONE        0x020   /* Enabwe/Disabwe Side Tone                             */
#define     APANA_SIDETONE_ATTN          0x0C0   /* Side Tone Attenuation                                */
#define     APANA_ENABWE_MIC_BOOST2      0x100   /* Secondawy Micwophone Ampwifiew gain boostew contwow  */

/*Digitaw Audio Path Contwow (SSM2602_WEG_DIGITAW_PATH)*/
#define     APDIGI_ENABWE_ADC_HPF         0x001   /* Enabwe/Disabwe ADC Highpass Fiwtew                   */
#define     APDIGI_DE_EMPHASIS            0x006   /* De-Emphasis Contwow                                  */
#define     APDIGI_ENABWE_DAC_MUTE        0x008   /* DAC Mute Contwow                                     */
#define     APDIGI_STOWE_OFFSET           0x010   /* Stowe/Cweaw DC offset when HPF is disabwed           */

/*Powew Down Contwow (SSM2602_WEG_POWEW)
 *(1=Enabwe PowewDown, 0=Disabwe PowewDown)
 */
#define     PWW_WINE_IN_PDN            0x001   /* Wine Input Powew Down                                */
#define     PWW_MIC_PDN                0x002   /* Micwophone Input & Bias Powew Down                   */
#define     PWW_ADC_PDN                0x004   /* ADC Powew Down                                       */
#define     PWW_DAC_PDN                0x008   /* DAC Powew Down                                       */
#define     PWW_OUT_PDN                0x010   /* Outputs Powew Down                                   */
#define     PWW_OSC_PDN                0x020   /* Osciwwatow Powew Down                                */
#define     PWW_CWK_OUT_PDN            0x040   /* CWKOUT Powew Down                                    */
#define     PWW_POWEW_OFF              0x080   /* POWEWOFF Mode                                        */

/*Digitaw Audio Intewface Fowmat (SSM2602_WEG_DIGITAW_IFACE)*/
#define     IFACE_IFACE_FOWMAT           0x003   /* Digitaw Audio input fowmat contwow                   */
#define     IFACE_AUDIO_DATA_WEN         0x00C   /* Audio Data wowd wength contwow                       */
#define     IFACE_DAC_WW_POWAWITY        0x010   /* Powawity Contwow fow cwocks in WJ,WJ and I2S modes   */
#define     IFACE_DAC_WW_SWAP            0x020   /* Swap DAC data contwow                                */
#define     IFACE_ENABWE_MASTEW          0x040   /* Enabwe/Disabwe Mastew Mode                           */
#define     IFACE_BCWK_INVEWT            0x080   /* Bit Cwock Invewsion contwow                          */

/*Sampwing Contwow (SSM2602_WEG_SAMPWING_CTWW)*/
#define     SWATE_ENABWE_USB_MODE        0x001   /* Enabwe/Disabwe USB Mode                              */
#define     SWATE_BOS_WATE               0x002   /* Base Ovew-Sampwing wate                              */
#define     SWATE_SAMPWE_WATE            0x03C   /* Cwock setting condition (Sampwing wate contwow)      */
#define     SWATE_COWECWK_DIV2           0x040   /* Cowe Cwock dividew sewect                            */
#define     SWATE_CWKOUT_DIV2            0x080   /* Cwock Out dividew sewect                             */

/*Active Contwow (SSM2602_WEG_ACTIVE_CTWW)*/
#define     ACTIVE_ACTIVATE_CODEC         0x001   /* Activate Codec Digitaw Audio Intewface               */

/*********************************************************************/

#define SSM2602_CACHEWEGNUM 	10

enum ssm2602_cwk {
	SSM2602_SYSCWK,
	SSM2602_CWK_CWKOUT,
	SSM2602_CWK_XTO
};

#endif
