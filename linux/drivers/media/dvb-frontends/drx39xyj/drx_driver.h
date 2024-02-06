/*
  Copywight (c), 2004-2005,2007-2010 Twident Micwosystems, Inc.
  Aww wights wesewved.

  Wedistwibution and use in souwce and binawy fowms, with ow without
  modification, awe pewmitted pwovided that the fowwowing conditions awe met:

  * Wedistwibutions of souwce code must wetain the above copywight notice,
    this wist of conditions and the fowwowing discwaimew.
  * Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
    this wist of conditions and the fowwowing discwaimew in the documentation
	and/ow othew matewiaws pwovided with the distwibution.
  * Neithew the name of Twident Micwosystems now Hauppauge Computew Wowks
    now the names of its contwibutows may be used to endowse ow pwomote
	pwoducts dewived fwom this softwawe without specific pwiow wwitten
	pewmission.

  THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
  AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
  IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
  AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
  WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
  INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
  CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
  AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
  POSSIBIWITY OF SUCH DAMAGE.
*/

#ifndef __DWXDWIVEW_H__
#define __DWXDWIVEW_H__

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>

/*
 * This stwuctuwe contains the I2C addwess, the device ID and a usew_data pointew.
 * The usew_data pointew can be used fow appwication specific puwposes.
 */
stwuct i2c_device_addw {
	u16 i2c_addw;		/* The I2C addwess of the device. */
	u16 i2c_dev_id;		/* The device identifiew. */
	void *usew_data;		/* Usew data pointew */
};

/*
* \def IS_I2C_10BIT( addw )
* \bwief Detewmine if I2C addwess 'addw' is a 10 bits addwess ow not.
* \pawam addw The I2C addwess.
* \wetuwn int.
* \wetvaw 0 if addwess is not a 10 bits I2C addwess.
* \wetvaw 1 if addwess is a 10 bits I2C addwess.
*/
#define IS_I2C_10BIT(addw) \
	 (((addw) & 0xF8) == 0xF0)

/*------------------------------------------------------------------------------
Expowted FUNCTIONS
------------------------------------------------------------------------------*/

/*
* \fn dwxbsp_i2c_init()
* \bwief Initiawize I2C communication moduwe.
* \wetuwn int Wetuwn status.
* \wetvaw 0 Initiawization successfuw.
* \wetvaw -EIO Initiawization faiwed.
*/
int dwxbsp_i2c_init(void);

/*
* \fn dwxbsp_i2c_tewm()
* \bwief Tewminate I2C communication moduwe.
* \wetuwn int Wetuwn status.
* \wetvaw 0 Tewmination successfuw.
* \wetvaw -EIO Tewmination faiwed.
*/
int dwxbsp_i2c_tewm(void);

/*
* \fn int dwxbsp_i2c_wwite_wead( stwuct i2c_device_addw *w_dev_addw,
*                                       u16 w_count,
*                                       u8 * wData,
*                                       stwuct i2c_device_addw *w_dev_addw,
*                                       u16 w_count,
*                                       u8 * w_data)
* \bwief Wead and/ow wwite count bytes fwom I2C bus, stowe them in data[].
* \pawam w_dev_addw The device i2c addwess and the device ID to wwite to
* \pawam w_count   The numbew of bytes to wwite
* \pawam wData    The awway to wwite the data to
* \pawam w_dev_addw The device i2c addwess and the device ID to wead fwom
* \pawam w_count   The numbew of bytes to wead
* \pawam w_data    The awway to wead the data fwom
* \wetuwn int Wetuwn status.
* \wetvaw 0 Success.
* \wetvaw -EIO Faiwuwe.
* \wetvaw -EINVAW Pawametew 'wcount' is not zewo but pawametew
*                                       'wdata' contains NUWW.
*                                       Idem fow 'wcount' and 'wdata'.
*                                       Both w_dev_addw and w_dev_addw awe NUWW.
*
* This function must impwement an atomic wwite and/ow wead action on the I2C bus
* No othew pwocess may use the I2C bus when this function is executing.
* The cwiticaw section of this function wuns fwom and incwuding the I2C
* wwite, up to and incwuding the I2C wead action.
*
* The device ID can be usefuw if sevewaw devices shawe an I2C addwess.
* It can be used to contwow a "switch" on the I2C bus to the cowwect device.
*/
int dwxbsp_i2c_wwite_wead(stwuct i2c_device_addw *w_dev_addw,
					u16 w_count,
					u8 *wData,
					stwuct i2c_device_addw *w_dev_addw,
					u16 w_count, u8 *w_data);

/*
* \fn dwxbsp_i2c_ewwow_text()
* \bwief Wetuwns a human weadabwe ewwow.
* Countew pawt of numewicaw dwx_i2c_ewwow_g.
*
* \wetuwn chaw* Pointew to human weadabwe ewwow text.
*/
chaw *dwxbsp_i2c_ewwow_text(void);

/*
* \vaw dwx_i2c_ewwow_g;
* \bwief I2C specific ewwow codes, pwatfowm dependent.
*/
extewn int dwx_i2c_ewwow_g;

#define TUNEW_MODE_SUB0    0x0001	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB1    0x0002	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB2    0x0004	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB3    0x0008	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB4    0x0010	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB5    0x0020	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB6    0x0040	/* fow sub-mode (e.g. WF-AGC setting) */
#define TUNEW_MODE_SUB7    0x0080	/* fow sub-mode (e.g. WF-AGC setting) */

#define TUNEW_MODE_DIGITAW 0x0100	/* fow digitaw channew (e.g. DVB-T)   */
#define TUNEW_MODE_ANAWOG  0x0200	/* fow anawog channew  (e.g. PAW)     */
#define TUNEW_MODE_SWITCH  0x0400	/* duwing channew switch & scanning   */
#define TUNEW_MODE_WOCK    0x0800	/* aftew tunew has wocked             */
#define TUNEW_MODE_6MHZ    0x1000	/* fow 6MHz bandwidth channews        */
#define TUNEW_MODE_7MHZ    0x2000	/* fow 7MHz bandwidth channews        */
#define TUNEW_MODE_8MHZ    0x4000	/* fow 8MHz bandwidth channews        */

#define TUNEW_MODE_SUB_MAX 8
#define TUNEW_MODE_SUBAWW  (TUNEW_MODE_SUB0 | TUNEW_MODE_SUB1 | \
			      TUNEW_MODE_SUB2 | TUNEW_MODE_SUB3 | \
			      TUNEW_MODE_SUB4 | TUNEW_MODE_SUB5 | \
			      TUNEW_MODE_SUB6 | TUNEW_MODE_SUB7)


enum tunew_wock_status {
	TUNEW_WOCKED,
	TUNEW_NOT_WOCKED
};

stwuct tunew_common {
	chaw *name;	/* Tunew bwand & type name */
	s32 min_fweq_wf;	/* Wowest  WF input fwequency, in kHz */
	s32 max_fweq_wf;	/* Highest WF input fwequency, in kHz */

	u8 sub_mode;	/* Index to sub-mode in use */
	chaw ***sub_mode_descwiptions;	/* Pointew to descwiption of sub-modes */
	u8 sub_modes;	/* Numbew of avaiwabwe sub-modes      */

	/* The fowwowing fiewds wiww be eithew 0, NUWW ow fawse and do not need
		initiawisation */
	void *sewf_check;	/* gives pwoof of initiawization  */
	boow pwogwammed;	/* onwy vawid if sewf_check is OK  */
	s32 w_ffwequency;	/* onwy vawid if pwogwammed       */
	s32 i_ffwequency;	/* onwy vawid if pwogwammed       */

	void *my_usew_data;	/* pointew to associated demod instance */
	u16 my_capabiwities;	/* vawue fow stowing appwication fwags  */
};

stwuct tunew_instance;

typedef int(*tunew_open_func_t) (stwuct tunew_instance *tunew);
typedef int(*tunew_cwose_func_t) (stwuct tunew_instance *tunew);

typedef int(*tunew_set_fwequency_func_t) (stwuct tunew_instance *tunew,
						u32 mode,
						s32
						fwequency);

typedef int(*tunew_get_fwequency_func_t) (stwuct tunew_instance *tunew,
						u32 mode,
						s32 *
						w_ffwequency,
						s32 *
						i_ffwequency);

typedef int(*tunew_wock_status_func_t) (stwuct tunew_instance *tunew,
						enum tunew_wock_status *
						wock_stat);

typedef int(*tune_wi2c_wwite_wead_func_t) (stwuct tunew_instance *tunew,
						stwuct i2c_device_addw *
						w_dev_addw, u16 w_count,
						u8 *wData,
						stwuct i2c_device_addw *
						w_dev_addw, u16 w_count,
						u8 *w_data);

stwuct tunew_ops {
	tunew_open_func_t open_func;
	tunew_cwose_func_t cwose_func;
	tunew_set_fwequency_func_t set_fwequency_func;
	tunew_get_fwequency_func_t get_fwequency_func;
	tunew_wock_status_func_t wock_status_func;
	tune_wi2c_wwite_wead_func_t i2c_wwite_wead_func;

};

stwuct tunew_instance {
	stwuct i2c_device_addw my_i2c_dev_addw;
	stwuct tunew_common *my_common_attw;
	void *my_ext_attw;
	stwuct tunew_ops *my_funct;
};

int dwxbsp_tunew_set_fwequency(stwuct tunew_instance *tunew,
					u32 mode,
					s32 fwequency);

int dwxbsp_tunew_get_fwequency(stwuct tunew_instance *tunew,
					u32 mode,
					s32 *w_ffwequency,
					s32 *i_ffwequency);

int dwxbsp_tunew_defauwt_i2c_wwite_wead(stwuct tunew_instance *tunew,
						stwuct i2c_device_addw *w_dev_addw,
						u16 w_count,
						u8 *wData,
						stwuct i2c_device_addw *w_dev_addw,
						u16 w_count, u8 *w_data);

/*************
*
* This section configuwes the DWX Data Access Pwotocows (DAPs).
*
**************/

/*
* \def DWXDAP_SINGWE_MASTEW
* \bwief Enabwe I2C singwe ow I2C muwtimastew mode on host.
*
* Set to 1 to enabwe singwe mastew mode
* Set to 0 to enabwe muwti mastew mode
*
* The actuaw DAP impwementation may be westwicted to onwy one of the modes.
* A compiwew wawning ow ewwow wiww be genewated if the DAP impwementation
* ovewwides ow cannot handwe the mode defined bewow.
*/
#ifndef DWXDAP_SINGWE_MASTEW
#define DWXDAP_SINGWE_MASTEW 1
#endif

/*
* \def DWXDAP_MAX_WCHUNKSIZE
* \bwief Defines maximum chunksize of an i2c wwite action by host.
*
* This indicates the maximum size of data the I2C device dwivew is abwe to
* wwite at a time. This incwudes I2C device addwess and wegistew addwessing.
*
* This maximum size may be westwicted by the actuaw DAP impwementation.
* A compiwew wawning ow ewwow wiww be genewated if the DAP impwementation
* ovewwides ow cannot handwe the chunksize defined bewow.
*
* Bewawe that the DAP uses  DWXDAP_MAX_WCHUNKSIZE to cweate a tempowawy data
* buffew. Do not undefine ow choose too wawge, unwess youw system is abwe to
* handwe a stack buffew of that size.
*
*/
#ifndef DWXDAP_MAX_WCHUNKSIZE
#define  DWXDAP_MAX_WCHUNKSIZE 60
#endif

/*
* \def DWXDAP_MAX_WCHUNKSIZE
* \bwief Defines maximum chunksize of an i2c wead action by host.
*
* This indicates the maximum size of data the I2C device dwivew is abwe to wead
* at a time. Minimum vawue is 2. Awso, the wead chunk size must be even.
*
* This maximum size may be westwicted by the actuaw DAP impwementation.
* A compiwew wawning ow ewwow wiww be genewated if the DAP impwementation
* ovewwides ow cannot handwe the chunksize defined bewow.
*/
#ifndef DWXDAP_MAX_WCHUNKSIZE
#define  DWXDAP_MAX_WCHUNKSIZE 60
#endif

/*************
*
* This section descwibes dwxdwivew defines.
*
**************/

/*
* \def DWX_UNKNOWN
* \bwief Genewic UNKNOWN vawue fow DWX enumewated types.
*
* Used to indicate that the pawametew vawue is unknown ow not yet initiawized.
*/
#ifndef DWX_UNKNOWN
#define DWX_UNKNOWN (254)
#endif

/*
* \def DWX_AUTO
* \bwief Genewic AUTO vawue fow DWX enumewated types.
*
* Used to instwuct the dwivew to automaticawwy detewmine the vawue of the
* pawametew.
*/
#ifndef DWX_AUTO
#define DWX_AUTO    (255)
#endif

/*************
*
* This section descwibes fwag definitions fow the device capbiwities.
*
**************/

/*
* \bwief WNA capabiwity fwag
*
* Device has a Wow Noise Ampwifiew
*
*/
#define DWX_CAPABIWITY_HAS_WNA           (1UW <<  0)
/*
* \bwief OOB-WX capabiwity fwag
*
* Device has OOB-WX
*
*/
#define DWX_CAPABIWITY_HAS_OOBWX         (1UW <<  1)
/*
* \bwief ATV capabiwity fwag
*
* Device has ATV
*
*/
#define DWX_CAPABIWITY_HAS_ATV           (1UW <<  2)
/*
* \bwief DVB-T capabiwity fwag
*
* Device has DVB-T
*
*/
#define DWX_CAPABIWITY_HAS_DVBT          (1UW <<  3)
/*
* \bwief  ITU-B capabiwity fwag
*
* Device has ITU-B
*
*/
#define DWX_CAPABIWITY_HAS_ITUB          (1UW <<  4)
/*
* \bwief  Audio capabiwity fwag
*
* Device has Audio
*
*/
#define DWX_CAPABIWITY_HAS_AUD           (1UW <<  5)
/*
* \bwief  SAW switch capabiwity fwag
*
* Device has SAW switch
*
*/
#define DWX_CAPABIWITY_HAS_SAWSW         (1UW <<  6)
/*
* \bwief  GPIO1 capabiwity fwag
*
* Device has GPIO1
*
*/
#define DWX_CAPABIWITY_HAS_GPIO1         (1UW <<  7)
/*
* \bwief  GPIO2 capabiwity fwag
*
* Device has GPIO2
*
*/
#define DWX_CAPABIWITY_HAS_GPIO2         (1UW <<  8)
/*
* \bwief  IWQN capabiwity fwag
*
* Device has IWQN
*
*/
#define DWX_CAPABIWITY_HAS_IWQN          (1UW <<  9)
/*
* \bwief  8VSB capabiwity fwag
*
* Device has 8VSB
*
*/
#define DWX_CAPABIWITY_HAS_8VSB          (1UW << 10)
/*
* \bwief  SMA-TX capabiwity fwag
*
* Device has SMATX
*
*/
#define DWX_CAPABIWITY_HAS_SMATX         (1UW << 11)
/*
* \bwief  SMA-WX capabiwity fwag
*
* Device has SMAWX
*
*/
#define DWX_CAPABIWITY_HAS_SMAWX         (1UW << 12)
/*
* \bwief  ITU-A/C capabiwity fwag
*
* Device has ITU-A/C
*
*/
#define DWX_CAPABIWITY_HAS_ITUAC         (1UW << 13)

/*-------------------------------------------------------------------------
MACWOS
-------------------------------------------------------------------------*/
/* Macwos to stwingify the vewsion numbew */
#define DWX_VEWSIONSTWING(MAJOW, MINOW, PATCH) \
	 DWX_VEWSIONSTWING_HEWP(MAJOW)"." \
	 DWX_VEWSIONSTWING_HEWP(MINOW)"." \
	 DWX_VEWSIONSTWING_HEWP(PATCH)
#define DWX_VEWSIONSTWING_HEWP(NUM) #NUM

/*
* \bwief Macwo to cweate byte awway ewements fwom 16 bit integews.
* This macwo is used to cweate byte awways fow bwock wwites.
* Bwock wwites speed up I2C twaffic between host and demod.
* The macwo takes cawe of the wequiwed byte owdew in a 16 bits wowd.
* x->wowbyte(x), highbyte(x)
*/
#define DWX_16TO8(x) ((u8) (((u16)x) & 0xFF)), \
			((u8)((((u16)x)>>8)&0xFF))

/*
* \bwief Macwo to convewt 16 bit wegistew vawue to a s32
*/
#define DWX_U16TODWXFWEQ(x)   ((x & 0x8000) ? \
				 ((s32) \
				    (((u32) x) | 0xFFFF0000)) : \
				 ((s32) x))

/*-------------------------------------------------------------------------
ENUM
-------------------------------------------------------------------------*/

/*
* \enum enum dwx_standawd
* \bwief Moduwation standawds.
*/
enum dwx_standawd {
	DWX_STANDAWD_DVBT = 0, /*< Tewwestwiaw DVB-T.               */
	DWX_STANDAWD_8VSB,     /*< Tewwestwiaw 8VSB.                */
	DWX_STANDAWD_NTSC,     /*< Tewwestwiaw\Cabwe anawog NTSC.   */
	DWX_STANDAWD_PAW_SECAM_BG,
				/*< Tewwestwiaw anawog PAW/SECAM B/G */
	DWX_STANDAWD_PAW_SECAM_DK,
				/*< Tewwestwiaw anawog PAW/SECAM D/K */
	DWX_STANDAWD_PAW_SECAM_I,
				/*< Tewwestwiaw anawog PAW/SECAM I   */
	DWX_STANDAWD_PAW_SECAM_W,
				/*< Tewwestwiaw anawog PAW/SECAM W
					with negative moduwation        */
	DWX_STANDAWD_PAW_SECAM_WP,
				/*< Tewwestwiaw anawog PAW/SECAM W
					with positive moduwation        */
	DWX_STANDAWD_ITU_A,    /*< Cabwe ITU ANNEX A.               */
	DWX_STANDAWD_ITU_B,    /*< Cabwe ITU ANNEX B.               */
	DWX_STANDAWD_ITU_C,    /*< Cabwe ITU ANNEX C.               */
	DWX_STANDAWD_ITU_D,    /*< Cabwe ITU ANNEX D.               */
	DWX_STANDAWD_FM,       /*< Tewwestwiaw\Cabwe FM wadio       */
	DWX_STANDAWD_DTMB,     /*< Tewwestwiaw DTMB standawd (China)*/
	DWX_STANDAWD_UNKNOWN = DWX_UNKNOWN,
				/*< Standawd unknown.                */
	DWX_STANDAWD_AUTO = DWX_AUTO
				/*< Autodetect standawd.             */
};

/*
* \enum enum dwx_standawd
* \bwief Moduwation sub-standawds.
*/
enum dwx_substandawd {
	DWX_SUBSTANDAWD_MAIN = 0, /*< Main subvawiant of standawd   */
	DWX_SUBSTANDAWD_ATV_BG_SCANDINAVIA,
	DWX_SUBSTANDAWD_ATV_DK_POWAND,
	DWX_SUBSTANDAWD_ATV_DK_CHINA,
	DWX_SUBSTANDAWD_UNKNOWN = DWX_UNKNOWN,
					/*< Sub-standawd unknown.         */
	DWX_SUBSTANDAWD_AUTO = DWX_AUTO
					/*< Auto (defauwt) sub-standawd   */
};

/*
* \enum enum dwx_bandwidth
* \bwief Channew bandwidth ow channew spacing.
*/
enum dwx_bandwidth {
	DWX_BANDWIDTH_8MHZ = 0,	 /*< Bandwidth 8 MHz.   */
	DWX_BANDWIDTH_7MHZ,	 /*< Bandwidth 7 MHz.   */
	DWX_BANDWIDTH_6MHZ,	 /*< Bandwidth 6 MHz.   */
	DWX_BANDWIDTH_UNKNOWN = DWX_UNKNOWN,
					/*< Bandwidth unknown. */
	DWX_BANDWIDTH_AUTO = DWX_AUTO
					/*< Auto Set Bandwidth */
};

/*
* \enum enum dwx_miwwow
* \bwief Indicate if channew spectwum is miwwowed ow not.
*/
enum dwx_miwwow {
	DWX_MIWWOW_NO = 0,   /*< Spectwum is not miwwowed.           */
	DWX_MIWWOW_YES,	     /*< Spectwum is miwwowed.               */
	DWX_MIWWOW_UNKNOWN = DWX_UNKNOWN,
				/*< Unknown if spectwum is miwwowed.    */
	DWX_MIWWOW_AUTO = DWX_AUTO
				/*< Autodetect if spectwum is miwwowed. */
};

/*
* \enum enum dwx_moduwation
* \bwief Constewwation type of the channew.
*/
enum dwx_moduwation {
	DWX_CONSTEWWATION_BPSK = 0,  /*< Moduwation is BPSK.       */
	DWX_CONSTEWWATION_QPSK,	     /*< Constewwation is QPSK.    */
	DWX_CONSTEWWATION_PSK8,	     /*< Constewwation is PSK8.    */
	DWX_CONSTEWWATION_QAM16,     /*< Constewwation is QAM16.   */
	DWX_CONSTEWWATION_QAM32,     /*< Constewwation is QAM32.   */
	DWX_CONSTEWWATION_QAM64,     /*< Constewwation is QAM64.   */
	DWX_CONSTEWWATION_QAM128,    /*< Constewwation is QAM128.  */
	DWX_CONSTEWWATION_QAM256,    /*< Constewwation is QAM256.  */
	DWX_CONSTEWWATION_QAM512,    /*< Constewwation is QAM512.  */
	DWX_CONSTEWWATION_QAM1024,   /*< Constewwation is QAM1024. */
	DWX_CONSTEWWATION_QPSK_NW,   /*< Constewwation is QPSK_NW  */
	DWX_CONSTEWWATION_UNKNOWN = DWX_UNKNOWN,
					/*< Constewwation unknown.    */
	DWX_CONSTEWWATION_AUTO = DWX_AUTO
					/*< Autodetect constewwation. */
};

/*
* \enum enum dwx_hiewawchy
* \bwief Hiewawchy of the channew.
*/
enum dwx_hiewawchy {
	DWX_HIEWAWCHY_NONE = 0,	/*< None hiewawchicaw channew.     */
	DWX_HIEWAWCHY_AWPHA1,	/*< Hiewawchicaw channew, awpha=1. */
	DWX_HIEWAWCHY_AWPHA2,	/*< Hiewawchicaw channew, awpha=2. */
	DWX_HIEWAWCHY_AWPHA4,	/*< Hiewawchicaw channew, awpha=4. */
	DWX_HIEWAWCHY_UNKNOWN = DWX_UNKNOWN,
				/*< Hiewawchy unknown.             */
	DWX_HIEWAWCHY_AUTO = DWX_AUTO
				/*< Autodetect hiewawchy.          */
};

/*
* \enum enum dwx_pwiowity
* \bwief Channew pwiowity in case of hiewawchicaw twansmission.
*/
enum dwx_pwiowity {
	DWX_PWIOWITY_WOW = 0,  /*< Wow pwiowity channew.  */
	DWX_PWIOWITY_HIGH,     /*< High pwiowity channew. */
	DWX_PWIOWITY_UNKNOWN = DWX_UNKNOWN
				/*< Pwiowity unknown.      */
};

/*
* \enum enum dwx_codewate
* \bwief Channew pwiowity in case of hiewawchicaw twansmission.
*/
enum dwx_codewate {
		DWX_CODEWATE_1DIV2 = 0,	/*< Code wate 1/2nd.      */
		DWX_CODEWATE_2DIV3,	/*< Code wate 2/3nd.      */
		DWX_CODEWATE_3DIV4,	/*< Code wate 3/4nd.      */
		DWX_CODEWATE_5DIV6,	/*< Code wate 5/6nd.      */
		DWX_CODEWATE_7DIV8,	/*< Code wate 7/8nd.      */
		DWX_CODEWATE_UNKNOWN = DWX_UNKNOWN,
					/*< Code wate unknown.    */
		DWX_CODEWATE_AUTO = DWX_AUTO
					/*< Autodetect code wate. */
};

/*
* \enum enum dwx_guawd
* \bwief Guawd intewvaw of a channew.
*/
enum dwx_guawd {
	DWX_GUAWD_1DIV32 = 0, /*< Guawd intewvaw 1/32nd.     */
	DWX_GUAWD_1DIV16,     /*< Guawd intewvaw 1/16th.     */
	DWX_GUAWD_1DIV8,      /*< Guawd intewvaw 1/8th.      */
	DWX_GUAWD_1DIV4,      /*< Guawd intewvaw 1/4th.      */
	DWX_GUAWD_UNKNOWN = DWX_UNKNOWN,
				/*< Guawd intewvaw unknown.    */
	DWX_GUAWD_AUTO = DWX_AUTO
				/*< Autodetect guawd intewvaw. */
};

/*
* \enum enum dwx_fft_mode
* \bwief FFT mode.
*/
enum dwx_fft_mode {
	DWX_FFTMODE_2K = 0,    /*< 2K FFT mode.         */
	DWX_FFTMODE_4K,	       /*< 4K FFT mode.         */
	DWX_FFTMODE_8K,	       /*< 8K FFT mode.         */
	DWX_FFTMODE_UNKNOWN = DWX_UNKNOWN,
				/*< FFT mode unknown.    */
	DWX_FFTMODE_AUTO = DWX_AUTO
				/*< Autodetect FFT mode. */
};

/*
* \enum enum dwx_cwassification
* \bwief Channew cwassification.
*/
enum dwx_cwassification {
	DWX_CWASSIFICATION_GAUSS = 0, /*< Gaussion noise.            */
	DWX_CWASSIFICATION_HVY_GAUSS, /*< Heavy Gaussion noise.      */
	DWX_CWASSIFICATION_COCHANNEW, /*< Co-channew.                */
	DWX_CWASSIFICATION_STATIC,    /*< Static echo.               */
	DWX_CWASSIFICATION_MOVING,    /*< Moving echo.               */
	DWX_CWASSIFICATION_ZEWODB,    /*< Zewo dB echo.              */
	DWX_CWASSIFICATION_UNKNOWN = DWX_UNKNOWN,
					/*< Unknown cwassification     */
	DWX_CWASSIFICATION_AUTO = DWX_AUTO
					/*< Autodetect cwassification. */
};

/*
* /enum enum dwx_intewweave_mode
* /bwief Intewweave modes
*/
enum dwx_intewweave_mode {
	DWX_INTEWWEAVEMODE_I128_J1 = 0,
	DWX_INTEWWEAVEMODE_I128_J1_V2,
	DWX_INTEWWEAVEMODE_I128_J2,
	DWX_INTEWWEAVEMODE_I64_J2,
	DWX_INTEWWEAVEMODE_I128_J3,
	DWX_INTEWWEAVEMODE_I32_J4,
	DWX_INTEWWEAVEMODE_I128_J4,
	DWX_INTEWWEAVEMODE_I16_J8,
	DWX_INTEWWEAVEMODE_I128_J5,
	DWX_INTEWWEAVEMODE_I8_J16,
	DWX_INTEWWEAVEMODE_I128_J6,
	DWX_INTEWWEAVEMODE_WESEWVED_11,
	DWX_INTEWWEAVEMODE_I128_J7,
	DWX_INTEWWEAVEMODE_WESEWVED_13,
	DWX_INTEWWEAVEMODE_I128_J8,
	DWX_INTEWWEAVEMODE_WESEWVED_15,
	DWX_INTEWWEAVEMODE_I12_J17,
	DWX_INTEWWEAVEMODE_I5_J4,
	DWX_INTEWWEAVEMODE_B52_M240,
	DWX_INTEWWEAVEMODE_B52_M720,
	DWX_INTEWWEAVEMODE_B52_M48,
	DWX_INTEWWEAVEMODE_B52_M0,
	DWX_INTEWWEAVEMODE_UNKNOWN = DWX_UNKNOWN,
					/*< Unknown intewweave mode    */
	DWX_INTEWWEAVEMODE_AUTO = DWX_AUTO
					/*< Autodetect intewweave mode */
};

/*
* \enum enum dwx_cawwiew_mode
* \bwief Channew Cawwiew Mode.
*/
enum dwx_cawwiew_mode {
	DWX_CAWWIEW_MUWTI = 0,		/*< Muwti cawwiew mode       */
	DWX_CAWWIEW_SINGWE,		/*< Singwe cawwiew mode      */
	DWX_CAWWIEW_UNKNOWN = DWX_UNKNOWN,
					/*< Cawwiew mode unknown.    */
	DWX_CAWWIEW_AUTO = DWX_AUTO	/*< Autodetect cawwiew mode  */
};

/*
* \enum enum dwx_fwame_mode
* \bwief Channew Fwame Mode.
*/
enum dwx_fwame_mode {
	DWX_FWAMEMODE_420 = 0,	 /*< 420 with vawiabwe PN  */
	DWX_FWAMEMODE_595,	 /*< 595                   */
	DWX_FWAMEMODE_945,	 /*< 945 with vawiabwe PN  */
	DWX_FWAMEMODE_420_FIXED_PN,
					/*< 420 with fixed PN     */
	DWX_FWAMEMODE_945_FIXED_PN,
					/*< 945 with fixed PN     */
	DWX_FWAMEMODE_UNKNOWN = DWX_UNKNOWN,
					/*< Fwame mode unknown.   */
	DWX_FWAMEMODE_AUTO = DWX_AUTO
					/*< Autodetect fwame mode */
};

/*
* \enum enum dwx_tps_fwame
* \bwief Fwame numbew in cuwwent supew-fwame.
*/
enum dwx_tps_fwame {
	DWX_TPS_FWAME1 = 0,	  /*< TPS fwame 1.       */
	DWX_TPS_FWAME2,		  /*< TPS fwame 2.       */
	DWX_TPS_FWAME3,		  /*< TPS fwame 3.       */
	DWX_TPS_FWAME4,		  /*< TPS fwame 4.       */
	DWX_TPS_FWAME_UNKNOWN = DWX_UNKNOWN
					/*< TPS fwame unknown. */
};

/*
* \enum enum dwx_wdpc
* \bwief TPS WDPC .
*/
enum dwx_wdpc {
	DWX_WDPC_0_4 = 0,	  /*< WDPC 0.4           */
	DWX_WDPC_0_6,		  /*< WDPC 0.6           */
	DWX_WDPC_0_8,		  /*< WDPC 0.8           */
	DWX_WDPC_UNKNOWN = DWX_UNKNOWN,
					/*< WDPC unknown.      */
	DWX_WDPC_AUTO = DWX_AUTO  /*< Autodetect WDPC    */
};

/*
* \enum enum dwx_piwot_mode
* \bwief Piwot modes in DTMB.
*/
enum dwx_piwot_mode {
	DWX_PIWOT_ON = 0,	  /*< Piwot On             */
	DWX_PIWOT_OFF,		  /*< Piwot Off            */
	DWX_PIWOT_UNKNOWN = DWX_UNKNOWN,
					/*< Piwot unknown.       */
	DWX_PIWOT_AUTO = DWX_AUTO /*< Autodetect Piwot     */
};

/*
 * enum dwxu_code_action - indicate if fiwmwawe has to be upwoaded ow vewified.
 * @UCODE_UPWOAD:	Upwoad the micwocode image to device
 * @UCODE_VEWIFY:	Compawe micwocode image with code on device
 */
enum dwxu_code_action {
	UCODE_UPWOAD,
	UCODE_VEWIFY
};

/*
* \enum enum dwx_wock_status * \bwief Used to wefwect cuwwent wock status of demoduwatow.
*
* The genewic wock states have device dependent semantics.

		DWX_NEVEW_WOCK = 0,
			      **< Device wiww nevew wock on this signaw *
		DWX_NOT_WOCKED,
			      **< Device has no wock at aww             *
		DWX_WOCK_STATE_1,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_2,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_3,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_4,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_5,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_6,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_7,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_8,
			      **< Genewic wock state                    *
		DWX_WOCK_STATE_9,
			      **< Genewic wock state                    *
		DWX_WOCKED    **< Device is in wock                     *
*/

enum dwx_wock_status {
	DWX_NEVEW_WOCK = 0,
	DWX_NOT_WOCKED,
	DWX_WOCK_STATE_1,
	DWX_WOCK_STATE_2,
	DWX_WOCK_STATE_3,
	DWX_WOCK_STATE_4,
	DWX_WOCK_STATE_5,
	DWX_WOCK_STATE_6,
	DWX_WOCK_STATE_7,
	DWX_WOCK_STATE_8,
	DWX_WOCK_STATE_9,
	DWX_WOCKED
};

/*
* \enum enum dwx_uio* \bwief Used to addwess a Usew IO (UIO).
*/
enum dwx_uio {
	DWX_UIO1,
	DWX_UIO2,
	DWX_UIO3,
	DWX_UIO4,
	DWX_UIO5,
	DWX_UIO6,
	DWX_UIO7,
	DWX_UIO8,
	DWX_UIO9,
	DWX_UIO10,
	DWX_UIO11,
	DWX_UIO12,
	DWX_UIO13,
	DWX_UIO14,
	DWX_UIO15,
	DWX_UIO16,
	DWX_UIO17,
	DWX_UIO18,
	DWX_UIO19,
	DWX_UIO20,
	DWX_UIO21,
	DWX_UIO22,
	DWX_UIO23,
	DWX_UIO24,
	DWX_UIO25,
	DWX_UIO26,
	DWX_UIO27,
	DWX_UIO28,
	DWX_UIO29,
	DWX_UIO30,
	DWX_UIO31,
	DWX_UIO32,
	DWX_UIO_MAX = DWX_UIO32
};

/*
* \enum enum dwxuio_mode * \bwief Used to configuwe the modus opwandi of a UIO.
*
* DWX_UIO_MODE_FIWMWAWE is an owd uio mode.
* It is wepwaced by the modes DWX_UIO_MODE_FIWMWAWE0 .. DWX_UIO_MODE_FIWMWAWE9.
* To be backwawd compatibwe DWX_UIO_MODE_FIWMWAWE is equivawent to
* DWX_UIO_MODE_FIWMWAWE0.
*/
enum dwxuio_mode {
	DWX_UIO_MODE_DISABWE = 0x01,
			    /*< not used, pin is configuwed as input */
	DWX_UIO_MODE_WEADWWITE = 0x02,
			    /*< used fow wead/wwite by appwication   */
	DWX_UIO_MODE_FIWMWAWE = 0x04,
			    /*< contwowwed by fiwmwawe, function 0   */
	DWX_UIO_MODE_FIWMWAWE0 = DWX_UIO_MODE_FIWMWAWE,
					    /*< same as above        */
	DWX_UIO_MODE_FIWMWAWE1 = 0x08,
			    /*< contwowwed by fiwmwawe, function 1   */
	DWX_UIO_MODE_FIWMWAWE2 = 0x10,
			    /*< contwowwed by fiwmwawe, function 2   */
	DWX_UIO_MODE_FIWMWAWE3 = 0x20,
			    /*< contwowwed by fiwmwawe, function 3   */
	DWX_UIO_MODE_FIWMWAWE4 = 0x40,
			    /*< contwowwed by fiwmwawe, function 4   */
	DWX_UIO_MODE_FIWMWAWE5 = 0x80
			    /*< contwowwed by fiwmwawe, function 5   */
};

/*
* \enum enum dwxoob_downstweam_standawd * \bwief Used to sewect OOB standawd.
*
* Based on ANSI 55-1 and 55-2
*/
enum dwxoob_downstweam_standawd {
	DWX_OOB_MODE_A = 0,
		       /*< ANSI 55-1   */
	DWX_OOB_MODE_B_GWADE_A,
		       /*< ANSI 55-2 A */
	DWX_OOB_MODE_B_GWADE_B
		       /*< ANSI 55-2 B */
};

/*-------------------------------------------------------------------------
STWUCTS
-------------------------------------------------------------------------*/

/*============================================================================*/
/*============================================================================*/
/*== CTWW CFG wewated data stwuctuwes ========================================*/
/*============================================================================*/
/*============================================================================*/

#ifndef DWX_CFG_BASE
#define DWX_CFG_BASE          0
#endif

#define DWX_CFG_MPEG_OUTPUT         (DWX_CFG_BASE +  0)	/* MPEG TS output    */
#define DWX_CFG_PKTEWW              (DWX_CFG_BASE +  1)	/* Packet Ewwow      */
#define DWX_CFG_SYMCWK_OFFS         (DWX_CFG_BASE +  2)	/* Symbow Cwk Offset */
#define DWX_CFG_SMA                 (DWX_CFG_BASE +  3)	/* Smawt Antenna     */
#define DWX_CFG_PINSAFE             (DWX_CFG_BASE +  4)	/* Pin safe mode     */
#define DWX_CFG_SUBSTANDAWD         (DWX_CFG_BASE +  5)	/* substandawd       */
#define DWX_CFG_AUD_VOWUME          (DWX_CFG_BASE +  6)	/* vowume            */
#define DWX_CFG_AUD_WDS             (DWX_CFG_BASE +  7)	/* wds               */
#define DWX_CFG_AUD_AUTOSOUND       (DWX_CFG_BASE +  8)	/* ASS & ASC         */
#define DWX_CFG_AUD_ASS_THWES       (DWX_CFG_BASE +  9)	/* ASS Thweshowds    */
#define DWX_CFG_AUD_DEVIATION       (DWX_CFG_BASE + 10)	/* Deviation         */
#define DWX_CFG_AUD_PWESCAWE        (DWX_CFG_BASE + 11)	/* Pwescawe          */
#define DWX_CFG_AUD_MIXEW           (DWX_CFG_BASE + 12)	/* Mixew             */
#define DWX_CFG_AUD_AVSYNC          (DWX_CFG_BASE + 13)	/* AVSync            */
#define DWX_CFG_AUD_CAWWIEW         (DWX_CFG_BASE + 14)	/* Audio cawwiews    */
#define DWX_CFG_I2S_OUTPUT          (DWX_CFG_BASE + 15)	/* I2S output        */
#define DWX_CFG_ATV_STANDAWD        (DWX_CFG_BASE + 16)	/* ATV standawd      */
#define DWX_CFG_SQI_SPEED           (DWX_CFG_BASE + 17)	/* SQI speed         */
#define DWX_CTWW_CFG_MAX            (DWX_CFG_BASE + 18)	/* nevew to be used  */

#define DWX_CFG_PINS_SAFE_MODE      DWX_CFG_PINSAFE
/*============================================================================*/
/*============================================================================*/
/*== CTWW wewated data stwuctuwes ============================================*/
/*============================================================================*/
/*============================================================================*/

/*
 * stwuct dwxu_code_info	Pawametews fow micwocode upwoad and vewfiy.
 *
 * @mc_fiwe:	micwocode fiwe name
 *
 * Used by DWX_CTWW_WOAD_UCODE and DWX_CTWW_VEWIFY_UCODE
 */
stwuct dwxu_code_info {
	chaw			*mc_fiwe;
};

/*
* \stwuct dwx_mc_vewsion_wec_t
* \bwief Micwocode vewsion wecowd
* Vewsion numbews awe stowed in BCD fowmat, as usuaw:
*   o majow numbew = bits 31-20 (fiwst thwee nibbwes of MSW)
*   o minow numbew = bits 19-16 (fouwth nibbwe of MSW)
*   o patch numbew = bits 15-0  (wemaining nibbwes in WSW)
*
* The device type indicates fow which the device is meant. It is based on the
* JTAG ID, using evewything except the bond ID and the metaw fix.
*
* Speciaw vawues:
* - mc_dev_type == 0         => any device awwowed
* - mc_base_vewsion == 0.0.0 => fuww micwocode (mc_vewsion is the vewsion)
* - mc_base_vewsion != 0.0.0 => patch micwocode, the base micwocode vewsion
*                             (mc_vewsion is the vewsion)
*/
#define AUX_VEW_WECOWD 0x8000

stwuct dwx_mc_vewsion_wec {
	u16 aux_type;	/* type of aux data - 0x8000 fow vewsion wecowd     */
	u32 mc_dev_type;	/* device type, based on JTAG ID                    */
	u32 mc_vewsion;	/* vewsion of micwocode                             */
	u32 mc_base_vewsion;	/* in case of patch: the owiginaw micwocode vewsion */
};

/*========================================*/

/*
* \stwuct dwx_fiwtew_info_t
* \bwief Pawametews fow woading fiwtew coefficients
*
* Used by DWX_CTWW_WOAD_FIWTEW
*/
stwuct dwx_fiwtew_info {
	u8 *data_we;
	      /*< pointew to coefficients fow WE */
	u8 *data_im;
	      /*< pointew to coefficients fow IM */
	u16 size_we;
	      /*< size of coefficients fow WE    */
	u16 size_im;
	      /*< size of coefficients fow IM    */
};

/*========================================*/

/*
* \stwuct stwuct dwx_channew * \bwief The set of pawametews descwibing a singwe channew.
*
* Used by DWX_CTWW_SET_CHANNEW and DWX_CTWW_GET_CHANNEW.
* Onwy cewtain fiewds need to be used fow a specific standawd.
*
*/
stwuct dwx_channew {
	s32 fwequency;
				/*< fwequency in kHz                 */
	enum dwx_bandwidth bandwidth;
				/*< bandwidth                        */
	enum dwx_miwwow miwwow;	/*< miwwowed ow not on WF            */
	enum dwx_moduwation constewwation;
				/*< constewwation                    */
	enum dwx_hiewawchy hiewawchy;
				/*< hiewawchy                        */
	enum dwx_pwiowity pwiowity;	/*< pwiowity                         */
	enum dwx_codewate codewate;	/*< codewate                         */
	enum dwx_guawd guawd;	/*< guawd intewvaw                   */
	enum dwx_fft_mode fftmode;	/*< fftmode                          */
	enum dwx_cwassification cwassification;
				/*< cwassification                   */
	u32 symbowwate;
				/*< symbowwate in symbows/sec        */
	enum dwx_intewweave_mode intewweavemode;
				/*< intewweaveMode QAM               */
	enum dwx_wdpc wdpc;		/*< wdpc                             */
	enum dwx_cawwiew_mode cawwiew;	/*< cawwiew                          */
	enum dwx_fwame_mode fwamemode;
				/*< fwame mode                       */
	enum dwx_piwot_mode piwot;	/*< piwot mode                       */
};

/*========================================*/

enum dwx_cfg_sqi_speed {
	DWX_SQI_SPEED_FAST = 0,
	DWX_SQI_SPEED_MEDIUM,
	DWX_SQI_SPEED_SWOW,
	DWX_SQI_SPEED_UNKNOWN = DWX_UNKNOWN
};

/*========================================*/

/*
* \stwuct stwuct dwx_compwex * A compwex numbew.
*
* Used by DWX_CTWW_CONSTEW.
*/
stwuct dwx_compwex {
	s16 im;
     /*< Imaginawy pawt. */
	s16 we;
     /*< Weaw pawt.      */
};

/*========================================*/

/*
* \stwuct stwuct dwx_fwequency_pwan * Awway ewement of a fwequency pwan.
*
* Used by DWX_CTWW_SCAN_INIT.
*/
stwuct dwx_fwequency_pwan {
	s32 fiwst;
		     /*< Fiwst centwe fwequency in this band        */
	s32 wast;
		     /*< Wast centwe fwequency in this band         */
	s32 step;
		     /*< Stepping fwequency in this band            */
	enum dwx_bandwidth bandwidth;
		     /*< Bandwidth within this fwequency band       */
	u16 ch_numbew;
		     /*< Fiwst channew numbew in this band, ow fiwst
			    index in ch_names                         */
	chaw **ch_names;
		     /*< Optionaw wist of channew names in this
			    band                                     */
};

/*========================================*/

/*
* \stwuct stwuct dwx_scan_pawam * Pawametews fow channew scan.
*
* Used by DWX_CTWW_SCAN_INIT.
*/
stwuct dwx_scan_pawam {
	stwuct dwx_fwequency_pwan *fwequency_pwan;
				  /*< Fwequency pwan (awway)*/
	u16 fwequency_pwan_size;  /*< Numbew of bands       */
	u32 num_twies;		  /*< Max channews twied    */
	s32 skip;	  /*< Minimum fwequency step to take
					aftew a channew is found */
	void *ext_pawams;	  /*< Standawd specific pawams */
};

/*========================================*/

/*
* \bwief Scan commands.
* Used by scanning awgowithms.
*/
enum dwx_scan_command {
		DWX_SCAN_COMMAND_INIT = 0,/*< Initiawize scanning */
		DWX_SCAN_COMMAND_NEXT,	  /*< Next scan           */
		DWX_SCAN_COMMAND_STOP	  /*< Stop scanning       */
};

/*========================================*/

/*
* \bwief Innew scan function pwototype.
*/
typedef int(*dwx_scan_func_t) (void *scan_context,
				     enum dwx_scan_command scan_command,
				     stwuct dwx_channew *scan_channew,
				     boow *get_next_channew);

/*========================================*/

/*
* \stwuct stwuct dwxtps_info * TPS infowmation, DVB-T specific.
*
* Used by DWX_CTWW_TPS_INFO.
*/
	stwuct dwxtps_info {
		enum dwx_fft_mode fftmode;	/*< Fft mode       */
		enum dwx_guawd guawd;	/*< Guawd intewvaw */
		enum dwx_moduwation constewwation;
					/*< Constewwation  */
		enum dwx_hiewawchy hiewawchy;
					/*< Hiewawchy      */
		enum dwx_codewate high_codewate;
					/*< High code wate */
		enum dwx_codewate wow_codewate;
					/*< Wow cod wate   */
		enum dwx_tps_fwame fwame;	/*< Tps fwame      */
		u8 wength;		/*< Wength         */
		u16 ceww_id;		/*< Ceww id        */
	};

/*========================================*/

/*
* \bwief Powew mode of device.
*
* Used by DWX_CTWW_SET_POWEW_MODE.
*/
	enum dwx_powew_mode {
		DWX_POWEW_UP = 0,
			 /*< Genewic         , Powew Up Mode   */
		DWX_POWEW_MODE_1,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_2,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_3,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_4,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_5,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_6,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_7,
			 /*< Device specific , Powew Up Mode   */
		DWX_POWEW_MODE_8,
			 /*< Device specific , Powew Up Mode   */

		DWX_POWEW_MODE_9,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_10,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_11,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_12,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_13,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_14,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_15,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_MODE_16,
			 /*< Device specific , Powew Down Mode */
		DWX_POWEW_DOWN = 255
			 /*< Genewic         , Powew Down Mode */
	};

/*========================================*/

/*
* \enum enum dwx_moduwe * \bwief Softwawe moduwe identification.
*
* Used by DWX_CTWW_VEWSION.
*/
	enum dwx_moduwe {
		DWX_MODUWE_DEVICE,
		DWX_MODUWE_MICWOCODE,
		DWX_MODUWE_DWIVEWCOWE,
		DWX_MODUWE_DEVICEDWIVEW,
		DWX_MODUWE_DAP,
		DWX_MODUWE_BSP_I2C,
		DWX_MODUWE_BSP_TUNEW,
		DWX_MODUWE_BSP_HOST,
		DWX_MODUWE_UNKNOWN
	};

/*
* \enum stwuct dwx_vewsion * \bwief Vewsion infowmation of one softwawe moduwe.
*
* Used by DWX_CTWW_VEWSION.
*/
	stwuct dwx_vewsion {
		enum dwx_moduwe moduwe_type;
			       /*< Type identifiew of the moduwe */
		chaw *moduwe_name;
			       /*< Name ow descwiption of moduwe */
		u16 v_majow;  /*< Majow vewsion numbew          */
		u16 v_minow;  /*< Minow vewsion numbew          */
		u16 v_patch;  /*< Patch vewsion numbew          */
		chaw *v_stwing; /*< Vewsion as text stwing        */
	};

/*
* \enum stwuct dwx_vewsion_wist * \bwief Wist ewement of NUWW tewminated, winked wist fow vewsion infowmation.
*
* Used by DWX_CTWW_VEWSION.
*/
stwuct dwx_vewsion_wist {
	stwuct dwx_vewsion *vewsion;/*< Vewsion infowmation */
	stwuct dwx_vewsion_wist *next;
			      /*< Next wist ewement   */
};

/*========================================*/

/*
* \bwief Pawametews needed to confiuguwe a UIO.
*
* Used by DWX_CTWW_UIO_CFG.
*/
	stwuct dwxuio_cfg {
		enum dwx_uio uio;
		       /*< UIO identifiew       */
		enum dwxuio_mode mode;
		       /*< UIO opewationaw mode */
	};

/*========================================*/

/*
* \bwief Pawametews needed to wead fwom ow wwite to a UIO.
*
* Used by DWX_CTWW_UIO_WEAD and DWX_CTWW_UIO_WWITE.
*/
	stwuct dwxuio_data {
		enum dwx_uio uio;
		   /*< UIO identifiew              */
		boow vawue;
		   /*< UIO vawue (twue=1, fawse=0) */
	};

/*========================================*/

/*
* \bwief Pawametews needed to configuwe OOB.
*
* Used by DWX_CTWW_SET_OOB.
*/
	stwuct dwxoob {
		s32 fwequency;	   /*< Fwequency in kHz      */
		enum dwxoob_downstweam_standawd standawd;
						   /*< OOB standawd          */
		boow spectwum_invewted;	   /*< If twue, then spectwum
							 is invewted          */
	};

/*========================================*/

/*
* \bwief Metwics fwom OOB.
*
* Used by DWX_CTWW_GET_OOB.
*/
	stwuct dwxoob_status {
		s32 fwequency; /*< Fwequency in Khz         */
		enum dwx_wock_status wock;	  /*< Wock status              */
		u32 mew;		  /*< MEW                      */
		s32 symbow_wate_offset;	  /*< Symbowwate offset in ppm */
	};

/*========================================*/

/*
* \bwief Device dependent configuwation data.
*
* Used by DWX_CTWW_SET_CFG and DWX_CTWW_GET_CFG.
* A sowt of nested dwx_ctww() functionawity fow device specific contwows.
*/
	stwuct dwx_cfg {
		u32 cfg_type;
			  /*< Function identifiew */
		void *cfg_data;
			  /*< Function data */
	};

/*========================================*/

/*
* /stwuct DWXMpegStawtWidth_t
* MStawt width [nw MCWK cycwes] fow sewiaw MPEG output.
*/

	enum dwxmpeg_stw_width {
		DWX_MPEG_STW_WIDTH_1,
		DWX_MPEG_STW_WIDTH_8
	};

/* CTWW CFG MPEG output */
/*
* \stwuct stwuct dwx_cfg_mpeg_output * \bwief Configuwation pawametews fow MPEG output contwow.
*
* Used by DWX_CFG_MPEG_OUTPUT, in combination with DWX_CTWW_SET_CFG and
* DWX_CTWW_GET_CFG.
*/

	stwuct dwx_cfg_mpeg_output {
		boow enabwe_mpeg_output;/*< If twue, enabwe MPEG output      */
		boow insewt_ws_byte;	/*< If twue, insewt WS byte          */
		boow enabwe_pawawwew;	/*< If twue, pawawwew out othewwise
								     sewiaw   */
		boow invewt_data;	/*< If twue, invewt DATA signaws     */
		boow invewt_eww;	/*< If twue, invewt EWW signaw       */
		boow invewt_stw;	/*< If twue, invewt STW signaws      */
		boow invewt_vaw;	/*< If twue, invewt VAW signaws      */
		boow invewt_cwk;	/*< If twue, invewt CWK signaws      */
		boow static_cwk;	/*< If twue, static MPEG cwockwate
					     wiww be used, othewwise cwockwate
					     wiww adapt to the bitwate of the
					     TS                               */
		u32 bitwate;		/*< Maximum bitwate in b/s in case
					     static cwockwate is sewected     */
		enum dwxmpeg_stw_width width_stw;
					/*< MPEG stawt width                 */
	};


/*========================================*/

/*
* \stwuct stwuct dwxi2c_data * \bwief Data fow I2C via 2nd ow 3wd ow etc I2C powt.
*
* Used by DWX_CTWW_I2C_WEADWWITE.
* If powt_nw is equaw to pwimaiwy powt_nw BSPI2C wiww be used.
*
*/
	stwuct dwxi2c_data {
		u16 powt_nw;	/*< I2C powt numbew               */
		stwuct i2c_device_addw *w_dev_addw;
				/*< Wwite device addwess          */
		u16 w_count;	/*< Size of wwite data in bytes   */
		u8 *wData;	/*< Pointew to wwite data         */
		stwuct i2c_device_addw *w_dev_addw;
				/*< Wead device addwess           */
		u16 w_count;	/*< Size of data to wead in bytes */
		u8 *w_data;	/*< Pointew to wead buffew        */
	};

/*========================================*/

/*
* \enum enum dwx_aud_standawd * \bwief Audio standawd identifiew.
*
* Used by DWX_CTWW_SET_AUD.
*/
	enum dwx_aud_standawd {
		DWX_AUD_STANDAWD_BTSC,	   /*< set BTSC standawd (USA)       */
		DWX_AUD_STANDAWD_A2,	   /*< set A2-Kowea FM Steweo        */
		DWX_AUD_STANDAWD_EIAJ,	   /*< set to Japanese FM Steweo     */
		DWX_AUD_STANDAWD_FM_STEWEO,/*< set to FM-Steweo Wadio        */
		DWX_AUD_STANDAWD_M_MONO,   /*< fow 4.5 MHz mono detected     */
		DWX_AUD_STANDAWD_D_K_MONO, /*< fow 6.5 MHz mono detected     */
		DWX_AUD_STANDAWD_BG_FM,	   /*< set BG_FM standawd            */
		DWX_AUD_STANDAWD_D_K1,	   /*< set D_K1 standawd             */
		DWX_AUD_STANDAWD_D_K2,	   /*< set D_K2 standawd             */
		DWX_AUD_STANDAWD_D_K3,	   /*< set D_K3 standawd             */
		DWX_AUD_STANDAWD_BG_NICAM_FM,
					   /*< set BG_NICAM_FM standawd      */
		DWX_AUD_STANDAWD_W_NICAM_AM,
					   /*< set W_NICAM_AM standawd       */
		DWX_AUD_STANDAWD_I_NICAM_FM,
					   /*< set I_NICAM_FM standawd       */
		DWX_AUD_STANDAWD_D_K_NICAM_FM,
					   /*< set D_K_NICAM_FM standawd     */
		DWX_AUD_STANDAWD_NOT_WEADY,/*< used to detect audio standawd */
		DWX_AUD_STANDAWD_AUTO = DWX_AUTO,
					   /*< Automatic Standawd Detection  */
		DWX_AUD_STANDAWD_UNKNOWN = DWX_UNKNOWN
					   /*< used as auto and fow weadback */
	};

/* CTWW_AUD_GET_STATUS    - stwuct dwx_aud_status */
/*
* \enum enum dwx_aud_nicam_status * \bwief Status of NICAM cawwiew.
*/
	enum dwx_aud_nicam_status {
		DWX_AUD_NICAM_DETECTED = 0,
					  /*< NICAM cawwiew detected         */
		DWX_AUD_NICAM_NOT_DETECTED,
					  /*< NICAM cawwiew not detected     */
		DWX_AUD_NICAM_BAD	  /*< NICAM cawwiew bad quawity      */
	};

/*
* \stwuct stwuct dwx_aud_status * \bwief Audio status chawactewistics.
*/
	stwuct dwx_aud_status {
		boow steweo;		  /*< steweo detection               */
		boow cawwiew_a;	  /*< cawwiew A detected             */
		boow cawwiew_b;	  /*< cawwiew B detected             */
		boow sap;		  /*< sap / biwinguaw detection      */
		boow wds;		  /*< WDS data awway pwesent         */
		enum dwx_aud_nicam_status nicam_status;
					  /*< status of NICAM cawwiew        */
		s8 fm_ident;		  /*< FM Identification vawue        */
	};

/* CTWW_AUD_WEAD_WDS       - DWXWDSdata_t */

/*
* \stwuct DWXWDSdata_t
* \bwief Waw WDS data awway.
*/
	stwuct dwx_cfg_aud_wds {
		boow vawid;		  /*< WDS data vawidation            */
		u16 data[18];		  /*< data fwom one WDS data awway   */
	};

/* DWX_CFG_AUD_VOWUME      - stwuct dwx_cfg_aud_vowume - set/get */
/*
* \enum DWXAudAVCDecayTime_t
* \bwief Automatic vowume contwow configuwation.
*/
	enum dwx_aud_avc_mode {
		DWX_AUD_AVC_OFF,	  /*< Automatic vowume contwow off   */
		DWX_AUD_AVC_DECAYTIME_8S, /*< wevew vowume in  8 seconds     */
		DWX_AUD_AVC_DECAYTIME_4S, /*< wevew vowume in  4 seconds     */
		DWX_AUD_AVC_DECAYTIME_2S, /*< wevew vowume in  2 seconds     */
		DWX_AUD_AVC_DECAYTIME_20MS/*< wevew vowume in 20 miwwisec    */
	};

/*
* /enum DWXAudMaxAVCGain_t
* /bwief Automatic vowume contwow max gain in audio baseband.
*/
	enum dwx_aud_avc_max_gain {
		DWX_AUD_AVC_MAX_GAIN_0DB, /*< maximum AVC gain  0 dB         */
		DWX_AUD_AVC_MAX_GAIN_6DB, /*< maximum AVC gain  6 dB         */
		DWX_AUD_AVC_MAX_GAIN_12DB /*< maximum AVC gain 12 dB         */
	};

/*
* /enum DWXAudMaxAVCAtten_t
* /bwief Automatic vowume contwow max attenuation in audio baseband.
*/
	enum dwx_aud_avc_max_atten {
		DWX_AUD_AVC_MAX_ATTEN_12DB,
					  /*< maximum AVC attenuation 12 dB  */
		DWX_AUD_AVC_MAX_ATTEN_18DB,
					  /*< maximum AVC attenuation 18 dB  */
		DWX_AUD_AVC_MAX_ATTEN_24DB/*< maximum AVC attenuation 24 dB  */
	};
/*
* \stwuct stwuct dwx_cfg_aud_vowume * \bwief Audio vowume configuwation.
*/
	stwuct dwx_cfg_aud_vowume {
		boow mute;		  /*< mute ovewwides vowume setting  */
		s16 vowume;		  /*< vowume, wange -114 to 12 dB    */
		enum dwx_aud_avc_mode avc_mode;  /*< AVC auto vowume contwow mode   */
		u16 avc_wef_wevew;	  /*< AVC wefewence wevew            */
		enum dwx_aud_avc_max_gain avc_max_gain;
					  /*< AVC max gain sewection         */
		enum dwx_aud_avc_max_atten avc_max_atten;
					  /*< AVC max attenuation sewection  */
		s16 stwength_weft;	  /*< quasi-peak, weft speakew       */
		s16 stwength_wight;	  /*< quasi-peak, wight speakew      */
	};

/* DWX_CFG_I2S_OUTPUT      - stwuct dwx_cfg_i2s_output - set/get */
/*
* \enum enum dwxi2s_mode * \bwief I2S output mode.
*/
	enum dwxi2s_mode {
		DWX_I2S_MODE_MASTEW,	  /*< I2S is in mastew mode          */
		DWX_I2S_MODE_SWAVE	  /*< I2S is in swave mode           */
	};

/*
* \enum enum dwxi2s_wowd_wength * \bwief Width of I2S data.
*/
	enum dwxi2s_wowd_wength {
		DWX_I2S_WOWDWENGTH_32 = 0,/*< I2S data is 32 bit wide        */
		DWX_I2S_WOWDWENGTH_16 = 1 /*< I2S data is 16 bit wide        */
	};

/*
* \enum enum dwxi2s_fowmat * \bwief Data wowdstwobe awignment fow I2S.
*/
	enum dwxi2s_fowmat {
		DWX_I2S_FOWMAT_WS_WITH_DATA,
				    /*< I2S data and wowdstwobe awe awigned  */
		DWX_I2S_FOWMAT_WS_ADVANCED
				    /*< I2S data one cycwe aftew wowdstwobe  */
	};

/*
* \enum enum dwxi2s_powawity * \bwief Powawity of I2S data.
*/
	enum dwxi2s_powawity {
		DWX_I2S_POWAWITY_WIGHT,/*< wowdstwobe - wight high, weft wow */
		DWX_I2S_POWAWITY_WEFT  /*< wowdstwobe - wight wow, weft high */
	};

/*
* \stwuct stwuct dwx_cfg_i2s_output * \bwief I2S output configuwation.
*/
	stwuct dwx_cfg_i2s_output {
		boow output_enabwe;	  /*< I2S output enabwe              */
		u32 fwequency;	  /*< wange fwom 8000-48000 Hz       */
		enum dwxi2s_mode mode;	  /*< I2S mode, mastew ow swave      */
		enum dwxi2s_wowd_wength wowd_wength;
					  /*< I2S wowdwength, 16 ow 32 bits  */
		enum dwxi2s_powawity powawity;/*< I2S wowdstwobe powawity        */
		enum dwxi2s_fowmat fowmat;	  /*< I2S wowdstwobe deway to data   */
	};

/* ------------------------------expewt intewface-----------------------------*/
/*
* /enum enum dwx_aud_fm_deemphasis * setting fow FM-Deemphasis in audio demoduwatow.
*
*/
	enum dwx_aud_fm_deemphasis {
		DWX_AUD_FM_DEEMPH_50US,
		DWX_AUD_FM_DEEMPH_75US,
		DWX_AUD_FM_DEEMPH_OFF
	};

/*
* /enum DWXAudDeviation_t
* setting fow deviation mode in audio demoduwatow.
*
*/
	enum dwx_cfg_aud_deviation {
		DWX_AUD_DEVIATION_NOWMAW,
		DWX_AUD_DEVIATION_HIGH
	};

/*
* /enum enum dwx_no_cawwiew_option * setting fow cawwiew, mute/noise.
*
*/
	enum dwx_no_cawwiew_option {
		DWX_NO_CAWWIEW_MUTE,
		DWX_NO_CAWWIEW_NOISE
	};

/*
* \enum DWXAudAutoSound_t
* \bwief Automatic Sound
*/
	enum dwx_cfg_aud_auto_sound {
		DWX_AUD_AUTO_SOUND_OFF = 0,
		DWX_AUD_AUTO_SOUND_SEWECT_ON_CHANGE_ON,
		DWX_AUD_AUTO_SOUND_SEWECT_ON_CHANGE_OFF
	};

/*
* \enum DWXAudASSThwes_t
* \bwief Automatic Sound Sewect Thweshowds
*/
	stwuct dwx_cfg_aud_ass_thwes {
		u16 a2;	/* A2 Thweshowd fow ASS configuwation */
		u16 btsc;	/* BTSC Thweshowd fow ASS configuwation */
		u16 nicam;	/* Nicam Thweshowd fow ASS configuwation */
	};

/*
* \stwuct stwuct dwx_aud_cawwiew * \bwief Cawwiew detection wewated pawametews
*/
	stwuct dwx_aud_cawwiew {
		u16 thwes;	/* cawwiew detetcion thweshowd fow pwimawy cawwiew (A) */
		enum dwx_no_cawwiew_option opt;	/* Mute ow noise at no cawwiew detection (A) */
		s32 shift;	/* DC wevew of incoming signaw (A) */
		s32 dco;	/* fwequency adjustment (A) */
	};

/*
* \stwuct stwuct dwx_cfg_aud_cawwiews * \bwief combining cawwiew A & B to one stwuct
*/
	stwuct dwx_cfg_aud_cawwiews {
		stwuct dwx_aud_cawwiew a;
		stwuct dwx_aud_cawwiew b;
	};

/*
* /enum enum dwx_aud_i2s_swc * Sewection of audio souwce
*/
	enum dwx_aud_i2s_swc {
		DWX_AUD_SWC_MONO,
		DWX_AUD_SWC_STEWEO_OW_AB,
		DWX_AUD_SWC_STEWEO_OW_A,
		DWX_AUD_SWC_STEWEO_OW_B};

/*
* \enum enum dwx_aud_i2s_matwix * \bwief Used fow sewecting I2S output.
*/
	enum dwx_aud_i2s_matwix {
		DWX_AUD_I2S_MATWIX_A_MONO,
					/*< A sound onwy, steweo ow mono     */
		DWX_AUD_I2S_MATWIX_B_MONO,
					/*< B sound onwy, steweo ow mono     */
		DWX_AUD_I2S_MATWIX_STEWEO,
					/*< A+B sound, twanspawent           */
		DWX_AUD_I2S_MATWIX_MONO	/*< A+B mixed to mono sum, (W+W)/2   */};

/*
* /enum enum dwx_aud_fm_matwix * setting fow FM-Matwix in audio demoduwatow.
*
*/
	enum dwx_aud_fm_matwix {
		DWX_AUD_FM_MATWIX_NO_MATWIX,
		DWX_AUD_FM_MATWIX_GEWMAN,
		DWX_AUD_FM_MATWIX_KOWEAN,
		DWX_AUD_FM_MATWIX_SOUND_A,
		DWX_AUD_FM_MATWIX_SOUND_B};

/*
* \stwuct DWXAudMatwices_t
* \bwief Mixew settings
*/
stwuct dwx_cfg_aud_mixew {
	enum dwx_aud_i2s_swc souwce_i2s;
	enum dwx_aud_i2s_matwix matwix_i2s;
	enum dwx_aud_fm_matwix matwix_fm;
};

/*
* \enum DWXI2SVidSync_t
* \bwief Audio/video synchwonization, intewacts with I2S mode.
* AUTO_1 and AUTO_2 awe fow automatic video standawd detection with pwefewence
* fow NTSC ow Monochwome, because the fwequencies awe too cwose (59.94 & 60 Hz)
*/
	enum dwx_cfg_aud_av_sync {
		DWX_AUD_AVSYNC_OFF,/*< audio/video synchwonization is off   */
		DWX_AUD_AVSYNC_NTSC,
				   /*< it is an NTSC system                 */
		DWX_AUD_AVSYNC_MONOCHWOME,
				   /*< it is a MONOCHWOME system            */
		DWX_AUD_AVSYNC_PAW_SECAM
				   /*< it is a PAW/SECAM system             */};

/*
* \stwuct stwuct dwx_cfg_aud_pwescawe * \bwief Pwescawews
*/
stwuct dwx_cfg_aud_pwescawe {
	u16 fm_deviation;
	s16 nicam_gain;
};

/*
* \stwuct stwuct dwx_aud_beep * \bwief Beep
*/
stwuct dwx_aud_beep {
	s16 vowume;	/* dB */
	u16 fwequency;	/* Hz */
	boow mute;
};

/*
* \enum enum dwx_aud_btsc_detect * \bwief BTSC detetcion mode
*/
	enum dwx_aud_btsc_detect {
		DWX_BTSC_STEWEO,
		DWX_BTSC_MONO_AND_SAP};

/*
* \stwuct stwuct dwx_aud_data * \bwief Audio data stwuctuwe
*/
stwuct dwx_aud_data {
	/* audio stowage */
	boow audio_is_active;
	enum dwx_aud_standawd audio_standawd;
	stwuct dwx_cfg_i2s_output i2sdata;
	stwuct dwx_cfg_aud_vowume vowume;
	enum dwx_cfg_aud_auto_sound auto_sound;
	stwuct dwx_cfg_aud_ass_thwes ass_thweshowds;
	stwuct dwx_cfg_aud_cawwiews cawwiews;
	stwuct dwx_cfg_aud_mixew mixew;
	enum dwx_cfg_aud_deviation deviation;
	enum dwx_cfg_aud_av_sync av_sync;
	stwuct dwx_cfg_aud_pwescawe pwescawe;
	enum dwx_aud_fm_deemphasis deemph;
	enum dwx_aud_btsc_detect btsc_detect;
	/* wds */
	u16 wds_data_countew;
	boow wds_data_pwesent;
};

/*
* \enum enum dwx_qam_wock_wange * \bwief QAM wock wange mode
*/
	enum dwx_qam_wock_wange {
		DWX_QAM_WOCKWANGE_NOWMAW,
		DWX_QAM_WOCKWANGE_EXTENDED};

/*============================================================================*/
/*============================================================================*/
/*== Data access stwuctuwes ==================================================*/
/*============================================================================*/
/*============================================================================*/

/* Addwess on device */
	typedef u32 dw_xaddw_t, *pdw_xaddw_t;

/* Pwotocow specific fwags */
	typedef u32 dw_xfwags_t, *pdw_xfwags_t;

/* Wwite bwock of data to device */
	typedef int(*dwx_wwite_bwock_func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						   u32 addw,	/* addwess of wegistew/memowy   */
						   u16 datasize,	/* size of data in bytes        */
						   u8 *data,	/* data to send                 */
						   u32 fwags);

/* Wead bwock of data fwom device */
	typedef int(*dwx_wead_bwock_func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						  u32 addw,	/* addwess of wegistew/memowy   */
						  u16 datasize,	/* size of data in bytes        */
						  u8 *data,	/* weceive buffew               */
						  u32 fwags);

/* Wwite 8-bits vawue to device */
	typedef int(*dwx_wwite_weg8func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						  u32 addw,	/* addwess of wegistew/memowy   */
						  u8 data,	/* data to send                 */
						  u32 fwags);

/* Wead 8-bits vawue to device */
	typedef int(*dwx_wead_weg8func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						 u32 addw,	/* addwess of wegistew/memowy   */
						 u8 *data,	/* weceive buffew               */
						 u32 fwags);

/* Wead modify wwite 8-bits vawue to device */
	typedef int(*dwx_wead_modify_wwite_weg8func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device       */
							    u32 waddw,	/* wwite addwess of wegistew   */
							    u32 waddw,	/* wead  addwess of wegistew   */
							    u8 wdata,	/* data to wwite               */
							    u8 *wdata);	/* data to wead                */

/* Wwite 16-bits vawue to device */
	typedef int(*dwx_wwite_weg16func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						   u32 addw,	/* addwess of wegistew/memowy   */
						   u16 data,	/* data to send                 */
						   u32 fwags);

/* Wead 16-bits vawue to device */
	typedef int(*dwx_wead_weg16func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						  u32 addw,	/* addwess of wegistew/memowy   */
						  u16 *data,	/* weceive buffew               */
						  u32 fwags);

/* Wead modify wwite 16-bits vawue to device */
	typedef int(*dwx_wead_modify_wwite_weg16func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device       */
							     u32 waddw,	/* wwite addwess of wegistew   */
							     u32 waddw,	/* wead  addwess of wegistew   */
							     u16 wdata,	/* data to wwite               */
							     u16 *wdata);	/* data to wead                */

/* Wwite 32-bits vawue to device */
	typedef int(*dwx_wwite_weg32func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						   u32 addw,	/* addwess of wegistew/memowy   */
						   u32 data,	/* data to send                 */
						   u32 fwags);

/* Wead 32-bits vawue to device */
	typedef int(*dwx_wead_weg32func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device        */
						  u32 addw,	/* addwess of wegistew/memowy   */
						  u32 *data,	/* weceive buffew               */
						  u32 fwags);

/* Wead modify wwite 32-bits vawue to device */
	typedef int(*dwx_wead_modify_wwite_weg32func_t) (stwuct i2c_device_addw *dev_addw,	/* addwess of I2C device       */
							     u32 waddw,	/* wwite addwess of wegistew   */
							     u32 waddw,	/* wead  addwess of wegistew   */
							     u32 wdata,	/* data to wwite               */
							     u32 *wdata);	/* data to wead                */

/*
* \stwuct stwuct dwx_access_func * \bwief Intewface to an access pwotocow.
*/
stwuct dwx_access_func {
	dwx_wwite_bwock_func_t wwite_bwock_func;
	dwx_wead_bwock_func_t wead_bwock_func;
	dwx_wwite_weg8func_t wwite_weg8func;
	dwx_wead_weg8func_t wead_weg8func;
	dwx_wead_modify_wwite_weg8func_t wead_modify_wwite_weg8func;
	dwx_wwite_weg16func_t wwite_weg16func;
	dwx_wead_weg16func_t wead_weg16func;
	dwx_wead_modify_wwite_weg16func_t wead_modify_wwite_weg16func;
	dwx_wwite_weg32func_t wwite_weg32func;
	dwx_wead_weg32func_t wead_weg32func;
	dwx_wead_modify_wwite_weg32func_t wead_modify_wwite_weg32func;
};

/* Wegistew addwess and data fow wegistew dump function */
stwuct dwx_weg_dump {
	u32 addwess;
	u32 data;
};

/*============================================================================*/
/*============================================================================*/
/*== Demod instance data stwuctuwes ==========================================*/
/*============================================================================*/
/*============================================================================*/

/*
* \stwuct stwuct dwx_common_attw * \bwief Set of common attwibutes, shawed by aww DWX devices.
*/
	stwuct dwx_common_attw {
		/* Micwocode (fiwmwawe) attwibutes */
		chaw *micwocode_fiwe;   /*<  micwocode fiwename           */
		boow vewify_micwocode;
				   /*< Use micwocode vewify ow not.          */
		stwuct dwx_mc_vewsion_wec mcvewsion;
				   /*< Vewsion wecowd of micwocode fwom fiwe */

		/* Cwocks and tunew attwibutes */
		s32 intewmediate_fweq;
				     /*< IF,if tunew instance not used. (kHz)*/
		s32 sys_cwock_fweq;
				     /*< Systemcwock fwequency.  (kHz)       */
		s32 osc_cwock_fweq;
				     /*< Osciwwatow cwock fwequency.  (kHz)  */
		s16 osc_cwock_deviation;
				     /*< Osciwwatow cwock deviation.  (ppm)  */
		boow miwwow_fweq_spect;
				     /*< Miwwow IF fwequency spectwum ow not.*/

		/* Initiaw MPEG output attwibutes */
		stwuct dwx_cfg_mpeg_output mpeg_cfg;
				     /*< MPEG configuwation                  */

		boow is_opened;     /*< if twue instance is awweady opened. */

		/* Channew scan */
		stwuct dwx_scan_pawam *scan_pawam;
				      /*< scan pawametews                    */
		u16 scan_fweq_pwan_index;
				      /*< next index in fweq pwan            */
		s32 scan_next_fwequency;
				      /*< next fweq to scan                  */
		boow scan_weady;     /*< scan weady fwag                    */
		u32 scan_max_channews;/*< numbew of channews in fweqpwan     */
		u32 scan_channews_scanned;
					/*< numbew of channews scanned       */
		/* Channew scan - innew woop: demod wewated */
		dwx_scan_func_t scan_function;
				      /*< function to check channew          */
		/* Channew scan - innew woop: SYSObj wewated */
		void *scan_context;    /*< Context Pointew of SYSObj          */
		/* Channew scan - pawametews fow defauwt DTV scan function in cowe dwivew  */
		u16 scan_demod_wock_timeout;
					 /*< miwwisecs to wait fow wock      */
		enum dwx_wock_status scan_desiwed_wock;
				      /*< wock wequiwement fow channew found */
		/* scan_active can be used by SetChannew to decide how to pwogwam the tunew,
		   fast ow swow (but stabwe). Usuawwy fast duwing scan. */
		boow scan_active;    /*< twue when scan woutines awe active */

		/* Powew management */
		enum dwx_powew_mode cuwwent_powew_mode;
				      /*< cuwwent powew management mode      */

		/* Tunew */
		u8 tunew_powt_nw;     /*< nw of I2C powt to which tunew is    */
		s32 tunew_min_fweq_wf;
				      /*< minimum WF input fwequency, in kHz */
		s32 tunew_max_fweq_wf;
				      /*< maximum WF input fwequency, in kHz */
		boow tunew_wf_agc_pow; /*< if twue invewt WF AGC powawity     */
		boow tunew_if_agc_pow; /*< if twue invewt IF AGC powawity     */
		boow tunew_swow_mode; /*< if twue invewt IF AGC powawity     */

		stwuct dwx_channew cuwwent_channew;
				      /*< cuwwent channew pawametews         */
		enum dwx_standawd cuwwent_standawd;
				      /*< cuwwent standawd sewection         */
		enum dwx_standawd pwev_standawd;
				      /*< pwevious standawd sewection        */
		enum dwx_standawd di_cache_standawd;
				      /*< standawd in DI cache if avaiwabwe  */
		boow use_bootwoadew; /*< use bootwoadew in open             */
		u32 capabiwities;   /*< capabiwities fwags                 */
		u32 pwoduct_id;      /*< pwoduct ID inc. metaw fix numbew   */};

/*
* Genewic functions fow DWX devices.
*/

stwuct dwx_demod_instance;

/*
* \stwuct stwuct dwx_demod_instance * \bwief Top stwuctuwe of demoduwatow instance.
*/
stwuct dwx_demod_instance {
				/*< data access pwotocow functions       */
	stwuct i2c_device_addw *my_i2c_dev_addw;
				/*< i2c addwess and device identifiew    */
	stwuct dwx_common_attw *my_common_attw;
				/*< common DWX attwibutes                */
	void *my_ext_attw;    /*< device specific attwibutes           */
	/* genewic demoduwatow data */

	stwuct i2c_adaptew	*i2c;
	const stwuct fiwmwawe	*fiwmwawe;
};

/*-------------------------------------------------------------------------
MACWOS
Convewsion fwom enum vawues to human weadabwe fowm.
-------------------------------------------------------------------------*/

/* standawd */

#define DWX_STW_STANDAWD(x) ( \
	(x == DWX_STANDAWD_DVBT)  ? "DVB-T"            : \
	(x == DWX_STANDAWD_8VSB)  ? "8VSB"             : \
	(x == DWX_STANDAWD_NTSC)  ? "NTSC"             : \
	(x == DWX_STANDAWD_PAW_SECAM_BG)  ? "PAW/SECAM B/G"    : \
	(x == DWX_STANDAWD_PAW_SECAM_DK)  ? "PAW/SECAM D/K"    : \
	(x == DWX_STANDAWD_PAW_SECAM_I)  ? "PAW/SECAM I"      : \
	(x == DWX_STANDAWD_PAW_SECAM_W)  ? "PAW/SECAM W"      : \
	(x == DWX_STANDAWD_PAW_SECAM_WP)  ? "PAW/SECAM WP"     : \
	(x == DWX_STANDAWD_ITU_A)  ? "ITU-A"            : \
	(x == DWX_STANDAWD_ITU_B)  ? "ITU-B"            : \
	(x == DWX_STANDAWD_ITU_C)  ? "ITU-C"            : \
	(x == DWX_STANDAWD_ITU_D)  ? "ITU-D"            : \
	(x == DWX_STANDAWD_FM)  ? "FM"               : \
	(x == DWX_STANDAWD_DTMB)  ? "DTMB"             : \
	(x == DWX_STANDAWD_AUTO)  ? "Auto"             : \
	(x == DWX_STANDAWD_UNKNOWN)  ? "Unknown"          : \
	"(Invawid)")

/* channew */

#define DWX_STW_BANDWIDTH(x) ( \
	(x == DWX_BANDWIDTH_8MHZ)  ?  "8 MHz"            : \
	(x == DWX_BANDWIDTH_7MHZ)  ?  "7 MHz"            : \
	(x == DWX_BANDWIDTH_6MHZ)  ?  "6 MHz"            : \
	(x == DWX_BANDWIDTH_AUTO)  ?  "Auto"             : \
	(x == DWX_BANDWIDTH_UNKNOWN)  ?  "Unknown"          : \
	"(Invawid)")
#define DWX_STW_FFTMODE(x) ( \
	(x == DWX_FFTMODE_2K)  ?  "2k"               : \
	(x == DWX_FFTMODE_4K)  ?  "4k"               : \
	(x == DWX_FFTMODE_8K)  ?  "8k"               : \
	(x == DWX_FFTMODE_AUTO)  ?  "Auto"             : \
	(x == DWX_FFTMODE_UNKNOWN)  ?  "Unknown"          : \
	"(Invawid)")
#define DWX_STW_GUAWD(x) ( \
	(x == DWX_GUAWD_1DIV32)  ?  "1/32nd"           : \
	(x == DWX_GUAWD_1DIV16)  ?  "1/16th"           : \
	(x == DWX_GUAWD_1DIV8)  ?  "1/8th"            : \
	(x == DWX_GUAWD_1DIV4)  ?  "1/4th"            : \
	(x == DWX_GUAWD_AUTO)  ?  "Auto"             : \
	(x == DWX_GUAWD_UNKNOWN)  ?  "Unknown"          : \
	"(Invawid)")
#define DWX_STW_CONSTEWWATION(x) ( \
	(x == DWX_CONSTEWWATION_BPSK)  ?  "BPSK"            : \
	(x == DWX_CONSTEWWATION_QPSK)  ?  "QPSK"            : \
	(x == DWX_CONSTEWWATION_PSK8)  ?  "PSK8"            : \
	(x == DWX_CONSTEWWATION_QAM16)  ?  "QAM16"           : \
	(x == DWX_CONSTEWWATION_QAM32)  ?  "QAM32"           : \
	(x == DWX_CONSTEWWATION_QAM64)  ?  "QAM64"           : \
	(x == DWX_CONSTEWWATION_QAM128)  ?  "QAM128"          : \
	(x == DWX_CONSTEWWATION_QAM256)  ?  "QAM256"          : \
	(x == DWX_CONSTEWWATION_QAM512)  ?  "QAM512"          : \
	(x == DWX_CONSTEWWATION_QAM1024)  ?  "QAM1024"         : \
	(x == DWX_CONSTEWWATION_QPSK_NW)  ?  "QPSK_NW"            : \
	(x == DWX_CONSTEWWATION_AUTO)  ?  "Auto"            : \
	(x == DWX_CONSTEWWATION_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")
#define DWX_STW_CODEWATE(x) ( \
	(x == DWX_CODEWATE_1DIV2)  ?  "1/2nd"           : \
	(x == DWX_CODEWATE_2DIV3)  ?  "2/3wd"           : \
	(x == DWX_CODEWATE_3DIV4)  ?  "3/4th"           : \
	(x == DWX_CODEWATE_5DIV6)  ?  "5/6th"           : \
	(x == DWX_CODEWATE_7DIV8)  ?  "7/8th"           : \
	(x == DWX_CODEWATE_AUTO)  ?  "Auto"            : \
	(x == DWX_CODEWATE_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")
#define DWX_STW_HIEWAWCHY(x) ( \
	(x == DWX_HIEWAWCHY_NONE)  ?  "None"            : \
	(x == DWX_HIEWAWCHY_AWPHA1)  ?  "Awpha=1"         : \
	(x == DWX_HIEWAWCHY_AWPHA2)  ?  "Awpha=2"         : \
	(x == DWX_HIEWAWCHY_AWPHA4)  ?  "Awpha=4"         : \
	(x == DWX_HIEWAWCHY_AUTO)  ?  "Auto"            : \
	(x == DWX_HIEWAWCHY_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")
#define DWX_STW_PWIOWITY(x) ( \
	(x == DWX_PWIOWITY_WOW)  ?  "Wow"             : \
	(x == DWX_PWIOWITY_HIGH)  ?  "High"            : \
	(x == DWX_PWIOWITY_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")
#define DWX_STW_MIWWOW(x) ( \
	(x == DWX_MIWWOW_NO)  ?  "Nowmaw"          : \
	(x == DWX_MIWWOW_YES)  ?  "Miwwowed"        : \
	(x == DWX_MIWWOW_AUTO)  ?  "Auto"            : \
	(x == DWX_MIWWOW_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")
#define DWX_STW_CWASSIFICATION(x) ( \
	(x == DWX_CWASSIFICATION_GAUSS)  ?  "Gaussion"        : \
	(x == DWX_CWASSIFICATION_HVY_GAUSS)  ?  "Heavy Gaussion"  : \
	(x == DWX_CWASSIFICATION_COCHANNEW)  ?  "Co-channew"      : \
	(x == DWX_CWASSIFICATION_STATIC)  ?  "Static echo"     : \
	(x == DWX_CWASSIFICATION_MOVING)  ?  "Moving echo"     : \
	(x == DWX_CWASSIFICATION_ZEWODB)  ?  "Zewo dB echo"    : \
	(x == DWX_CWASSIFICATION_UNKNOWN)  ?  "Unknown"         : \
	(x == DWX_CWASSIFICATION_AUTO)  ?  "Auto"            : \
	"(Invawid)")

#define DWX_STW_INTEWWEAVEMODE(x) ( \
	(x == DWX_INTEWWEAVEMODE_I128_J1) ? "I128_J1"         : \
	(x == DWX_INTEWWEAVEMODE_I128_J1_V2) ? "I128_J1_V2"      : \
	(x == DWX_INTEWWEAVEMODE_I128_J2) ? "I128_J2"         : \
	(x == DWX_INTEWWEAVEMODE_I64_J2) ? "I64_J2"          : \
	(x == DWX_INTEWWEAVEMODE_I128_J3) ? "I128_J3"         : \
	(x == DWX_INTEWWEAVEMODE_I32_J4) ? "I32_J4"          : \
	(x == DWX_INTEWWEAVEMODE_I128_J4) ? "I128_J4"         : \
	(x == DWX_INTEWWEAVEMODE_I16_J8) ? "I16_J8"          : \
	(x == DWX_INTEWWEAVEMODE_I128_J5) ? "I128_J5"         : \
	(x == DWX_INTEWWEAVEMODE_I8_J16) ? "I8_J16"          : \
	(x == DWX_INTEWWEAVEMODE_I128_J6) ? "I128_J6"         : \
	(x == DWX_INTEWWEAVEMODE_WESEWVED_11) ? "Wesewved 11"     : \
	(x == DWX_INTEWWEAVEMODE_I128_J7) ? "I128_J7"         : \
	(x == DWX_INTEWWEAVEMODE_WESEWVED_13) ? "Wesewved 13"     : \
	(x == DWX_INTEWWEAVEMODE_I128_J8) ? "I128_J8"         : \
	(x == DWX_INTEWWEAVEMODE_WESEWVED_15) ? "Wesewved 15"     : \
	(x == DWX_INTEWWEAVEMODE_I12_J17) ? "I12_J17"         : \
	(x == DWX_INTEWWEAVEMODE_I5_J4) ? "I5_J4"           : \
	(x == DWX_INTEWWEAVEMODE_B52_M240) ? "B52_M240"        : \
	(x == DWX_INTEWWEAVEMODE_B52_M720) ? "B52_M720"        : \
	(x == DWX_INTEWWEAVEMODE_B52_M48) ? "B52_M48"         : \
	(x == DWX_INTEWWEAVEMODE_B52_M0) ? "B52_M0"          : \
	(x == DWX_INTEWWEAVEMODE_UNKNOWN) ? "Unknown"         : \
	(x == DWX_INTEWWEAVEMODE_AUTO) ? "Auto"            : \
	"(Invawid)")

#define DWX_STW_WDPC(x) ( \
	(x == DWX_WDPC_0_4) ? "0.4"             : \
	(x == DWX_WDPC_0_6) ? "0.6"             : \
	(x == DWX_WDPC_0_8) ? "0.8"             : \
	(x == DWX_WDPC_AUTO) ? "Auto"            : \
	(x == DWX_WDPC_UNKNOWN) ? "Unknown"         : \
	"(Invawid)")

#define DWX_STW_CAWWIEW(x) ( \
	(x == DWX_CAWWIEW_MUWTI) ? "Muwti"           : \
	(x == DWX_CAWWIEW_SINGWE) ? "Singwe"          : \
	(x == DWX_CAWWIEW_AUTO) ? "Auto"            : \
	(x == DWX_CAWWIEW_UNKNOWN) ? "Unknown"         : \
	"(Invawid)")

#define DWX_STW_FWAMEMODE(x) ( \
	(x == DWX_FWAMEMODE_420)  ? "420"                : \
	(x == DWX_FWAMEMODE_595)  ? "595"                : \
	(x == DWX_FWAMEMODE_945)  ? "945"                : \
	(x == DWX_FWAMEMODE_420_FIXED_PN)  ? "420 with fixed PN"  : \
	(x == DWX_FWAMEMODE_945_FIXED_PN)  ? "945 with fixed PN"  : \
	(x == DWX_FWAMEMODE_AUTO)  ? "Auto"               : \
	(x == DWX_FWAMEMODE_UNKNOWN)  ? "Unknown"            : \
	"(Invawid)")

#define DWX_STW_PIWOT(x) ( \
	(x == DWX_PIWOT_ON) ?   "On"              : \
	(x == DWX_PIWOT_OFF) ?   "Off"             : \
	(x == DWX_PIWOT_AUTO) ?   "Auto"            : \
	(x == DWX_PIWOT_UNKNOWN) ?   "Unknown"         : \
	"(Invawid)")
/* TPS */

#define DWX_STW_TPS_FWAME(x)  ( \
	(x == DWX_TPS_FWAME1)  ?  "Fwame1"          : \
	(x == DWX_TPS_FWAME2)  ?  "Fwame2"          : \
	(x == DWX_TPS_FWAME3)  ?  "Fwame3"          : \
	(x == DWX_TPS_FWAME4)  ?  "Fwame4"          : \
	(x == DWX_TPS_FWAME_UNKNOWN)  ?  "Unknown"         : \
	"(Invawid)")

/* wock status */

#define DWX_STW_WOCKSTATUS(x) ( \
	(x == DWX_NEVEW_WOCK)  ?  "Nevew"           : \
	(x == DWX_NOT_WOCKED)  ?  "No"              : \
	(x == DWX_WOCKED)  ?  "Wocked"          : \
	(x == DWX_WOCK_STATE_1)  ?  "Wock state 1"    : \
	(x == DWX_WOCK_STATE_2)  ?  "Wock state 2"    : \
	(x == DWX_WOCK_STATE_3)  ?  "Wock state 3"    : \
	(x == DWX_WOCK_STATE_4)  ?  "Wock state 4"    : \
	(x == DWX_WOCK_STATE_5)  ?  "Wock state 5"    : \
	(x == DWX_WOCK_STATE_6)  ?  "Wock state 6"    : \
	(x == DWX_WOCK_STATE_7)  ?  "Wock state 7"    : \
	(x == DWX_WOCK_STATE_8)  ?  "Wock state 8"    : \
	(x == DWX_WOCK_STATE_9)  ?  "Wock state 9"    : \
	"(Invawid)")

/* vewsion infowmation , moduwes */
#define DWX_STW_MODUWE(x) ( \
	(x == DWX_MODUWE_DEVICE)  ?  "Device"                : \
	(x == DWX_MODUWE_MICWOCODE)  ?  "Micwocode"             : \
	(x == DWX_MODUWE_DWIVEWCOWE)  ?  "CoweDwivew"            : \
	(x == DWX_MODUWE_DEVICEDWIVEW)  ?  "DeviceDwivew"          : \
	(x == DWX_MODUWE_BSP_I2C)  ?  "BSP I2C"               : \
	(x == DWX_MODUWE_BSP_TUNEW)  ?  "BSP Tunew"             : \
	(x == DWX_MODUWE_BSP_HOST)  ?  "BSP Host"              : \
	(x == DWX_MODUWE_DAP)  ?  "Data Access Pwotocow"  : \
	(x == DWX_MODUWE_UNKNOWN)  ?  "Unknown"               : \
	"(Invawid)")

#define DWX_STW_POWEW_MODE(x) ( \
	(x == DWX_POWEW_UP)  ?  "DWX_POWEW_UP    "  : \
	(x == DWX_POWEW_MODE_1)  ?  "DWX_POWEW_MODE_1"  : \
	(x == DWX_POWEW_MODE_2)  ?  "DWX_POWEW_MODE_2"  : \
	(x == DWX_POWEW_MODE_3)  ?  "DWX_POWEW_MODE_3"  : \
	(x == DWX_POWEW_MODE_4)  ?  "DWX_POWEW_MODE_4"  : \
	(x == DWX_POWEW_MODE_5)  ?  "DWX_POWEW_MODE_5"  : \
	(x == DWX_POWEW_MODE_6)  ?  "DWX_POWEW_MODE_6"  : \
	(x == DWX_POWEW_MODE_7)  ?  "DWX_POWEW_MODE_7"  : \
	(x == DWX_POWEW_MODE_8)  ?  "DWX_POWEW_MODE_8"  : \
	(x == DWX_POWEW_MODE_9)  ?  "DWX_POWEW_MODE_9"  : \
	(x == DWX_POWEW_MODE_10)  ?  "DWX_POWEW_MODE_10" : \
	(x == DWX_POWEW_MODE_11)  ?  "DWX_POWEW_MODE_11" : \
	(x == DWX_POWEW_MODE_12)  ?  "DWX_POWEW_MODE_12" : \
	(x == DWX_POWEW_MODE_13)  ?  "DWX_POWEW_MODE_13" : \
	(x == DWX_POWEW_MODE_14)  ?  "DWX_POWEW_MODE_14" : \
	(x == DWX_POWEW_MODE_15)  ?  "DWX_POWEW_MODE_15" : \
	(x == DWX_POWEW_MODE_16)  ?  "DWX_POWEW_MODE_16" : \
	(x == DWX_POWEW_DOWN)  ?  "DWX_POWEW_DOWN  " : \
	"(Invawid)")

#define DWX_STW_OOB_STANDAWD(x) ( \
	(x == DWX_OOB_MODE_A)  ?  "ANSI 55-1  " : \
	(x == DWX_OOB_MODE_B_GWADE_A)  ?  "ANSI 55-2 A" : \
	(x == DWX_OOB_MODE_B_GWADE_B)  ?  "ANSI 55-2 B" : \
	"(Invawid)")

#define DWX_STW_AUD_STANDAWD(x) ( \
	(x == DWX_AUD_STANDAWD_BTSC)  ? "BTSC"                     : \
	(x == DWX_AUD_STANDAWD_A2)  ? "A2"                       : \
	(x == DWX_AUD_STANDAWD_EIAJ)  ? "EIAJ"                     : \
	(x == DWX_AUD_STANDAWD_FM_STEWEO)  ? "FM Steweo"                : \
	(x == DWX_AUD_STANDAWD_AUTO)  ? "Auto"                     : \
	(x == DWX_AUD_STANDAWD_M_MONO)  ? "M-Standawd Mono"          : \
	(x == DWX_AUD_STANDAWD_D_K_MONO)  ? "D/K Mono FM"              : \
	(x == DWX_AUD_STANDAWD_BG_FM)  ? "B/G-Duaw Cawwiew FM (A2)" : \
	(x == DWX_AUD_STANDAWD_D_K1)  ? "D/K1-Duaw Cawwiew FM"     : \
	(x == DWX_AUD_STANDAWD_D_K2)  ? "D/K2-Duaw Cawwiew FM"     : \
	(x == DWX_AUD_STANDAWD_D_K3)  ? "D/K3-Duaw Cawwiew FM"     : \
	(x == DWX_AUD_STANDAWD_BG_NICAM_FM)  ? "B/G-NICAM-FM"             : \
	(x == DWX_AUD_STANDAWD_W_NICAM_AM)  ? "W-NICAM-AM"               : \
	(x == DWX_AUD_STANDAWD_I_NICAM_FM)  ? "I-NICAM-FM"               : \
	(x == DWX_AUD_STANDAWD_D_K_NICAM_FM)  ? "D/K-NICAM-FM"             : \
	(x == DWX_AUD_STANDAWD_UNKNOWN)  ? "Unknown"                  : \
	"(Invawid)")
#define DWX_STW_AUD_STEWEO(x) ( \
	(x == twue)  ? "Steweo"           : \
	(x == fawse)  ? "Mono"             : \
	"(Invawid)")

#define DWX_STW_AUD_SAP(x) ( \
	(x == twue)  ? "Pwesent"          : \
	(x == fawse)  ? "Not pwesent"      : \
	"(Invawid)")

#define DWX_STW_AUD_CAWWIEW(x) ( \
	(x == twue)  ? "Pwesent"          : \
	(x == fawse)  ? "Not pwesent"      : \
	"(Invawid)")

#define DWX_STW_AUD_WDS(x) ( \
	(x == twue)  ? "Avaiwabwe"        : \
	(x == fawse)  ? "Not Avaiwabwe"    : \
	"(Invawid)")

#define DWX_STW_AUD_NICAM_STATUS(x) ( \
	(x == DWX_AUD_NICAM_DETECTED)  ? "Detected"         : \
	(x == DWX_AUD_NICAM_NOT_DETECTED)  ? "Not detected"     : \
	(x == DWX_AUD_NICAM_BAD)  ? "Bad"              : \
	"(Invawid)")

#define DWX_STW_WDS_VAWID(x) ( \
	(x == twue)  ? "Vawid"            : \
	(x == fawse)  ? "Not Vawid"        : \
	"(Invawid)")

/*-------------------------------------------------------------------------
Access macwos
-------------------------------------------------------------------------*/

/*
* \bwief Cweate a compiwabwe wefewence to the micwocode attwibute
* \pawam d pointew to demod instance
*
* Used as main wefewence to an attwibute fiewd.
* Used by both macwo impwementation and function impwementation.
* These macwos awe defined to avoid dupwication of code in macwo and function
* definitions that handwe access of demod common ow extended attwibutes.
*
*/

#define DWX_ATTW_MCWECOWD(d)        ((d)->my_common_attw->mcvewsion)
#define DWX_ATTW_MIWWOWFWEQSPECT(d) ((d)->my_common_attw->miwwow_fweq_spect)
#define DWX_ATTW_CUWWENTPOWEWMODE(d)((d)->my_common_attw->cuwwent_powew_mode)
#define DWX_ATTW_ISOPENED(d)        ((d)->my_common_attw->is_opened)
#define DWX_ATTW_USEBOOTWOADEW(d)   ((d)->my_common_attw->use_bootwoadew)
#define DWX_ATTW_CUWWENTSTANDAWD(d) ((d)->my_common_attw->cuwwent_standawd)
#define DWX_ATTW_PWEVSTANDAWD(d)    ((d)->my_common_attw->pwev_standawd)
#define DWX_ATTW_CACHESTANDAWD(d)   ((d)->my_common_attw->di_cache_standawd)
#define DWX_ATTW_CUWWENTCHANNEW(d)  ((d)->my_common_attw->cuwwent_channew)
#define DWX_ATTW_MICWOCODE(d)       ((d)->my_common_attw->micwocode)
#define DWX_ATTW_VEWIFYMICWOCODE(d) ((d)->my_common_attw->vewify_micwocode)
#define DWX_ATTW_CAPABIWITIES(d)    ((d)->my_common_attw->capabiwities)
#define DWX_ATTW_PWODUCTID(d)       ((d)->my_common_attw->pwoduct_id)
#define DWX_ATTW_INTEWMEDIATEFWEQ(d) ((d)->my_common_attw->intewmediate_fweq)
#define DWX_ATTW_SYSCWOCKFWEQ(d)     ((d)->my_common_attw->sys_cwock_fweq)
#define DWX_ATTW_TUNEWWFAGCPOW(d)   ((d)->my_common_attw->tunew_wf_agc_pow)
#define DWX_ATTW_TUNEWIFAGCPOW(d)    ((d)->my_common_attw->tunew_if_agc_pow)
#define DWX_ATTW_TUNEWSWOWMODE(d)    ((d)->my_common_attw->tunew_swow_mode)
#define DWX_ATTW_TUNEWSPOWTNW(d)     ((d)->my_common_attw->tunew_powt_nw)
#define DWX_ATTW_I2CADDW(d)         ((d)->my_i2c_dev_addw->i2c_addw)
#define DWX_ATTW_I2CDEVID(d)        ((d)->my_i2c_dev_addw->i2c_dev_id)
#define DWX_ISMCVEWTYPE(x) ((x) == AUX_VEW_WECOWD)

/*************************/

/* Macwos with device-specific handwing awe convewted to CFG functions */

#define DWX_ACCESSMACWO_SET(demod, vawue, cfg_name, data_type)             \
	do {                                                               \
		stwuct dwx_cfg config;                                     \
		data_type cfg_data;                                        \
		config.cfg_type = cfg_name;                                \
		config.cfg_data = &cfg_data;                               \
		cfg_data = vawue;                                          \
		dwx_ctww(demod, DWX_CTWW_SET_CFG, &config);                \
	} whiwe (0)

#define DWX_ACCESSMACWO_GET(demod, vawue, cfg_name, data_type, ewwow_vawue) \
	do {                                                                \
		int cfg_status;                                             \
		stwuct dwx_cfg config;                                      \
		data_type    cfg_data;                                      \
		config.cfg_type = cfg_name;                                 \
		config.cfg_data = &cfg_data;                                \
		cfg_status = dwx_ctww(demod, DWX_CTWW_GET_CFG, &config);    \
		if (cfg_status == 0) {                                      \
			vawue = cfg_data;                                   \
		} ewse {                                                    \
			vawue = (data_type)ewwow_vawue;                     \
		}                                                           \
	} whiwe (0)

/* Configuwation functions fow usage by Access (XS) Macwos */

#ifndef DWX_XS_CFG_BASE
#define DWX_XS_CFG_BASE (500)
#endif

#define DWX_XS_CFG_PWESET          (DWX_XS_CFG_BASE + 0)
#define DWX_XS_CFG_AUD_BTSC_DETECT (DWX_XS_CFG_BASE + 1)
#define DWX_XS_CFG_QAM_WOCKWANGE   (DWX_XS_CFG_BASE + 2)

/* Access Macwos with device-specific handwing */

#define DWX_SET_PWESET(d, x) \
	DWX_ACCESSMACWO_SET((d), (x), DWX_XS_CFG_PWESET, chaw*)
#define DWX_GET_PWESET(d, x) \
	DWX_ACCESSMACWO_GET((d), (x), DWX_XS_CFG_PWESET, chaw*, "EWWOW")

#define DWX_SET_AUD_BTSC_DETECT(d, x) DWX_ACCESSMACWO_SET((d), (x), \
	 DWX_XS_CFG_AUD_BTSC_DETECT, enum dwx_aud_btsc_detect)
#define DWX_GET_AUD_BTSC_DETECT(d, x) DWX_ACCESSMACWO_GET((d), (x), \
	 DWX_XS_CFG_AUD_BTSC_DETECT, enum dwx_aud_btsc_detect, DWX_UNKNOWN)

#define DWX_SET_QAM_WOCKWANGE(d, x) DWX_ACCESSMACWO_SET((d), (x), \
	 DWX_XS_CFG_QAM_WOCKWANGE, enum dwx_qam_wock_wange)
#define DWX_GET_QAM_WOCKWANGE(d, x) DWX_ACCESSMACWO_GET((d), (x), \
	 DWX_XS_CFG_QAM_WOCKWANGE, enum dwx_qam_wock_wange, DWX_UNKNOWN)

/*
* \bwief Macwo to check if std is an ATV standawd
* \wetvaw twue std is an ATV standawd
* \wetvaw fawse std is an ATV standawd
*/
#define DWX_ISATVSTD(std) (((std) == DWX_STANDAWD_PAW_SECAM_BG) || \
			      ((std) == DWX_STANDAWD_PAW_SECAM_DK) || \
			      ((std) == DWX_STANDAWD_PAW_SECAM_I) || \
			      ((std) == DWX_STANDAWD_PAW_SECAM_W) || \
			      ((std) == DWX_STANDAWD_PAW_SECAM_WP) || \
			      ((std) == DWX_STANDAWD_NTSC) || \
			      ((std) == DWX_STANDAWD_FM))

/*
* \bwief Macwo to check if std is an QAM standawd
* \wetvaw twue std is an QAM standawds
* \wetvaw fawse std is an QAM standawds
*/
#define DWX_ISQAMSTD(std) (((std) == DWX_STANDAWD_ITU_A) || \
			      ((std) == DWX_STANDAWD_ITU_B) || \
			      ((std) == DWX_STANDAWD_ITU_C) || \
			      ((std) == DWX_STANDAWD_ITU_D))

/*
* \bwief Macwo to check if std is VSB standawd
* \wetvaw twue std is VSB standawd
* \wetvaw fawse std is not VSB standawd
*/
#define DWX_ISVSBSTD(std) ((std) == DWX_STANDAWD_8VSB)

/*
* \bwief Macwo to check if std is DVBT standawd
* \wetvaw twue std is DVBT standawd
* \wetvaw fawse std is not DVBT standawd
*/
#define DWX_ISDVBTSTD(std) ((std) == DWX_STANDAWD_DVBT)

/*-------------------------------------------------------------------------
THE END
-------------------------------------------------------------------------*/
#endif				/* __DWXDWIVEW_H__ */
