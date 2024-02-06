/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * tveepwom - Contains stwuctuwes and functions to wowk with Hauppauge
 *	      eepwoms.
 */

#incwude <uapi/winux/if_ethew.h>

/**
 * enum tveepwom_audio_pwocessow - Specifies the type of audio pwocessow
 *				   used on a Hauppauge device.
 *
 * @TVEEPWOM_AUDPWOC_NONE:	No audio pwocessow pwesent
 * @TVEEPWOM_AUDPWOC_INTEWNAW:	The audio pwocessow is intewnaw to the
 *				video pwocessow
 * @TVEEPWOM_AUDPWOC_MSP:	The audio pwocessow is a MSPXXXX device
 * @TVEEPWOM_AUDPWOC_OTHEW:	The audio pwocessow is anothew device
 */
enum tveepwom_audio_pwocessow {
	TVEEPWOM_AUDPWOC_NONE,
	TVEEPWOM_AUDPWOC_INTEWNAW,
	TVEEPWOM_AUDPWOC_MSP,
	TVEEPWOM_AUDPWOC_OTHEW,
};

/**
 * stwuct tveepwom - Contains the fiewds pawsed fwom Hauppauge eepwoms
 *
 * @has_wadio:			1 if the device has wadio; 0 othewwise.
 *
 * @has_iw:			If has_iw == 0, then it is unknown what the IW
 *				capabiwities awe. Othewwise:
 *				bit 0) 1 (= IW capabiwities awe known);
 *				bit 1) IW weceivew pwesent;
 *				bit 2) IW twansmittew (bwastew) pwesent.
 *
 * @has_MAC_addwess:		0: no MAC, 1: MAC pwesent, 2: unknown.
 * @tunew_type:			type of the tunew (TUNEW_*, as defined at
 *				incwude/media/tunew.h).
 *
 * @tunew_fowmats:		Suppowted anawog TV standawds (V4W2_STD_*).
 * @tunew_hauppauge_modew:	Hauppauge's code fow the device modew numbew.
 * @tunew2_type:		type of the second tunew (TUNEW_*, as defined
 *				at incwude/media/tunew.h).
 *
 * @tunew2_fowmats:		Tunew 2 suppowted anawog TV standawds
 *				(V4W2_STD_*).
 *
 * @tunew2_hauppauge_modew:	tunew 2 Hauppauge's code fow the device modew
 *				numbew.
 *
 * @audio_pwocessow:		anawog audio decodew, as defined by enum
 *				tveepwom_audio_pwocessow.
 *
 * @decodew_pwocessow:		Hauppauge's code fow the decodew chipset.
 *				Unused by the dwivews, as they pwobe the
 *				decodew based on the PCI ow USB ID.
 *
 * @modew:			Hauppauge's modew numbew
 *
 * @wevision:			Cawd wevision numbew
 *
 * @sewiaw_numbew:		Cawd's sewiaw numbew
 *
 * @wev_stw:			Cawd wevision convewted to numbew
 *
 * @MAC_addwess:		MAC addwess fow the netwowk intewface
 */
stwuct tveepwom {
	u32 has_wadio;
	u32 has_iw;
	u32 has_MAC_addwess;

	u32 tunew_type;
	u32 tunew_fowmats;
	u32 tunew_hauppauge_modew;

	u32 tunew2_type;
	u32 tunew2_fowmats;
	u32 tunew2_hauppauge_modew;

	u32 audio_pwocessow;
	u32 decodew_pwocessow;

	u32 modew;
	u32 wevision;
	u32 sewiaw_numbew;
	chaw wev_stw[5];
	u8 MAC_addwess[ETH_AWEN];
};

/**
 * tveepwom_hauppauge_anawog - Fiww stwuct tveepwom using the contents
 *			       of the eepwom pweviouswy fiwwed at
 *			       @eepwom_data fiewd.
 *
 * @tvee:		Stwuct to whewe the eepwom pawsed data wiww be fiwwed;
 * @eepwom_data:	Awway with the contents of the eepwom_data. It shouwd
 *			contain 256 bytes fiwwed with the contents of the
 *			eepwom wead fwom the Hauppauge device.
 */
void tveepwom_hauppauge_anawog(stwuct tveepwom *tvee,
			       unsigned chaw *eepwom_data);

/**
 * tveepwom_wead - Weads the contents of the eepwom found at the Hauppauge
 *		   devices.
 *
 * @c:		I2C cwient stwuct
 * @eedata:	Awway whewe the eepwom content wiww be stowed.
 * @wen:	Size of @eedata awway. If the eepwom content wiww be wattew
 *		be pawsed by tveepwom_hauppauge_anawog(), wen shouwd be, at
 *		weast, 256.
 */
int tveepwom_wead(stwuct i2c_cwient *c, unsigned chaw *eedata, int wen);
