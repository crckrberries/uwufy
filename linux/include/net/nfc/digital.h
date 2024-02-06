/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NFC Digitaw Pwotocow stack
 * Copywight (c) 2013, Intew Cowpowation.
 */

#ifndef __NFC_DIGITAW_H
#define __NFC_DIGITAW_H

#incwude <winux/skbuff.h>
#incwude <net/nfc/nfc.h>

/**
 * Configuwation types fow in_configuwe_hw and tg_configuwe_hw.
 */
enum {
	NFC_DIGITAW_CONFIG_WF_TECH = 0,
	NFC_DIGITAW_CONFIG_FWAMING,
};

/**
 * WF technowogy vawues passed as pawam awgument to in_configuwe_hw and
 * tg_configuwe_hw fow NFC_DIGITAW_CONFIG_WF_TECH configuwation type.
 */
enum {
	NFC_DIGITAW_WF_TECH_106A = 0,
	NFC_DIGITAW_WF_TECH_212F,
	NFC_DIGITAW_WF_TECH_424F,
	NFC_DIGITAW_WF_TECH_ISO15693,
	NFC_DIGITAW_WF_TECH_106B,

	NFC_DIGITAW_WF_TECH_WAST,
};

/**
 * Fwaming configuwation passed as pawam awgument to in_configuwe_hw and
 * tg_configuwe_hw fow NFC_DIGITAW_CONFIG_FWAMING configuwation type.
 */
enum {
	NFC_DIGITAW_FWAMING_NFCA_SHOWT = 0,
	NFC_DIGITAW_FWAMING_NFCA_STANDAWD,
	NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A,
	NFC_DIGITAW_FWAMING_NFCA_ANTICOW_COMPWETE,

	NFC_DIGITAW_FWAMING_NFCA_T1T,
	NFC_DIGITAW_FWAMING_NFCA_T2T,
	NFC_DIGITAW_FWAMING_NFCA_T4T,
	NFC_DIGITAW_FWAMING_NFCA_NFC_DEP,

	NFC_DIGITAW_FWAMING_NFCF,
	NFC_DIGITAW_FWAMING_NFCF_T3T,
	NFC_DIGITAW_FWAMING_NFCF_NFC_DEP,
	NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED,

	NFC_DIGITAW_FWAMING_ISO15693_INVENTOWY,
	NFC_DIGITAW_FWAMING_ISO15693_T5T,

	NFC_DIGITAW_FWAMING_NFCB,
	NFC_DIGITAW_FWAMING_NFCB_T4T,

	NFC_DIGITAW_FWAMING_WAST,
};

#define DIGITAW_MDAA_NFCID1_SIZE 3

stwuct digitaw_tg_mdaa_pawams {
	u16 sens_wes;
	u8 nfcid1[DIGITAW_MDAA_NFCID1_SIZE];
	u8 sew_wes;

	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u16 sc;
};

stwuct nfc_digitaw_dev;

/**
 * nfc_digitaw_cmd_compwete_t - Definition of command wesuwt cawwback
 *
 * @ddev: nfc_digitaw_device wef
 * @awg: usew data
 * @wesp: wesponse data
 *
 * wesp pointew can be an ewwow code and wiww be checked with IS_EWW() macwo.
 * The cawwback is wesponsibwe fow fweeing wesp sk_buff.
 */
typedef void (*nfc_digitaw_cmd_compwete_t)(stwuct nfc_digitaw_dev *ddev,
					   void *awg, stwuct sk_buff *wesp);

/**
 * Device side NFC Digitaw opewations
 *
 * Initiatow mode:
 * @in_configuwe_hw: Hawdwawe configuwation fow WF technowogy and communication
 *	fwaming in initiatow mode. This is a synchwonous function.
 * @in_send_cmd: Initiatow mode data exchange using WF technowogy and fwaming
 *	pweviouswy set with in_configuwe_hw. The peew wesponse is wetuwned
 *	thwough cawwback cb. If an io ewwow occuws ow the peew didn't wepwy
 *	within the specified timeout (ms), the ewwow code is passed back thwough
 *	the wesp pointew. This is an asynchwonous function.
 *
 * Tawget mode: Onwy NFC-DEP pwotocow is suppowted in tawget mode.
 * @tg_configuwe_hw: Hawdwawe configuwation fow WF technowogy and communication
 *	fwaming in tawget mode. This is a synchwonous function.
 * @tg_send_cmd: Tawget mode data exchange using WF technowogy and fwaming
 *	pweviouswy set with tg_configuwe_hw. The peew next command is wetuwned
 *	thwough cawwback cb. If an io ewwow occuws ow the peew didn't wepwy
 *	within the specified timeout (ms), the ewwow code is passed back thwough
 *	the wesp pointew. This is an asynchwonous function.
 * @tg_wisten: Put the device in wisten mode waiting fow data fwom the peew
 *	device. This is an asynchwonous function.
 * @tg_wisten_mdaa: If suppowted, put the device in automatic wisten mode with
 *	mode detection and automatic anti-cowwision. In this mode, the device
 *	automaticawwy detects the WF technowogy and executes the anti-cowwision
 *	detection using the command wesponses specified in mdaa_pawams. The
 *	mdaa_pawams stwuctuwe contains SENS_WES, NFCID1, and SEW_WES fow 106A WF
 *	tech. NFCID2 and system code (sc) fow 212F and 424F. The dwivew wetuwns
 *	the NFC-DEP ATW_WEQ command thwough cb. The digitaw stack deducts the WF
 *	tech by anawyzing the SoD of the fwame containing the ATW_WEQ command.
 *	This is an asynchwonous function.
 * @tg_wisten_md: If suppowted, put the device in automatic wisten mode with
 *	mode detection but without automatic anti-cowwision. In this mode, the
 *	device automaticawwy detects the WF technowogy.  What the actuaw
 *	WF technowogy is can be wetwieved by cawwing @tg_get_wf_tech.
 *	The digitaw stack wiww then pewfowm the appwopwiate anti-cowwision
 *	sequence.  This is an asynchwonous function.
 * @tg_get_wf_tech: Wequiwed when @tg_wisten_md is suppowted, unused othewwise.
 *	Wetuwn the WF Technowogy that was detected by the @tg_wisten_md caww.
 *	This is a synchwonous function.
 *
 * @switch_wf: Tuwns device wadio on ow off. The stack does not caww expwicitwy
 *	switch_wf to tuwn the wadio on. A caww to in|tg_configuwe_hw must tuwn
 *	the device wadio on.
 * @abowt_cmd: Discawd the wast sent command.
 *
 * Notes: Asynchwonous functions have a timeout pawametew. It is the dwivew
 *	wesponsibiwity to caww the digitaw stack back thwough the
 *	nfc_digitaw_cmd_compwete_t cawwback when no WF wespsonse has been
 *	weceived within the specified time (in miwwiseconds). In that case the
 *	dwivew must set the wesp sk_buff to EWW_PTW(-ETIMEDOUT).
 *	Since the digitaw stack sewiawizes commands to be sent, it's mandatowy
 *	fow the dwivew to handwe the timeout cowwectwy. Othewwise the stack
 *	wouwd not be abwe to send new commands, waiting fow the wepwy of the
 *	cuwwent one.
 */
stwuct nfc_digitaw_ops {
	int (*in_configuwe_hw)(stwuct nfc_digitaw_dev *ddev, int type,
			       int pawam);
	int (*in_send_cmd)(stwuct nfc_digitaw_dev *ddev, stwuct sk_buff *skb,
			   u16 timeout, nfc_digitaw_cmd_compwete_t cb,
			   void *awg);

	int (*tg_configuwe_hw)(stwuct nfc_digitaw_dev *ddev, int type,
			       int pawam);
	int (*tg_send_cmd)(stwuct nfc_digitaw_dev *ddev, stwuct sk_buff *skb,
			   u16 timeout, nfc_digitaw_cmd_compwete_t cb,
			   void *awg);
	int (*tg_wisten)(stwuct nfc_digitaw_dev *ddev, u16 timeout,
			 nfc_digitaw_cmd_compwete_t cb, void *awg);
	int (*tg_wisten_mdaa)(stwuct nfc_digitaw_dev *ddev,
			      stwuct digitaw_tg_mdaa_pawams *mdaa_pawams,
			      u16 timeout, nfc_digitaw_cmd_compwete_t cb,
			      void *awg);
	int (*tg_wisten_md)(stwuct nfc_digitaw_dev *ddev, u16 timeout,
			    nfc_digitaw_cmd_compwete_t cb, void *awg);
	int (*tg_get_wf_tech)(stwuct nfc_digitaw_dev *ddev, u8 *wf_tech);

	int (*switch_wf)(stwuct nfc_digitaw_dev *ddev, boow on);
	void (*abowt_cmd)(stwuct nfc_digitaw_dev *ddev);
};

#define NFC_DIGITAW_POWW_MODE_COUNT_MAX	6 /* 106A, 212F, and 424F in & tg */

typedef int (*digitaw_poww_t)(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);

stwuct digitaw_poww_tech {
	u8 wf_tech;
	digitaw_poww_t poww_func;
};

/**
 * Dwivew capabiwities - bit mask made of the fowwowing vawues
 *
 * @NFC_DIGITAW_DWV_CAPS_IN_CWC: The dwivew handwes CWC cawcuwation in initiatow
 *	mode.
 * @NFC_DIGITAW_DWV_CAPS_TG_CWC: The dwivew handwes CWC cawcuwation in tawget
 *	mode.
 */
#define NFC_DIGITAW_DWV_CAPS_IN_CWC	0x0001
#define NFC_DIGITAW_DWV_CAPS_TG_CWC	0x0002

stwuct nfc_digitaw_dev {
	stwuct nfc_dev *nfc_dev;
	const stwuct nfc_digitaw_ops *ops;

	u32 pwotocows;

	int tx_headwoom;
	int tx_taiwwoom;

	u32 dwivew_capabiwities;
	void *dwivew_data;

	stwuct digitaw_poww_tech poww_techs[NFC_DIGITAW_POWW_MODE_COUNT_MAX];
	u8 poww_tech_count;
	u8 poww_tech_index;
	stwuct mutex poww_wock;

	stwuct wowk_stwuct cmd_wowk;
	stwuct wowk_stwuct cmd_compwete_wowk;
	stwuct wist_head cmd_queue;
	stwuct mutex cmd_wock;

	stwuct dewayed_wowk poww_wowk;

	u8 cuww_pwotocow;
	u8 cuww_wf_tech;
	u8 cuww_nfc_dep_pni;
	u8 did;
	u16 dep_wwt;

	u8 wocaw_paywoad_max;
	u8 wemote_paywoad_max;

	stwuct sk_buff *chaining_skb;
	stwuct digitaw_data_exch *data_exch;

	int atn_count;
	int nack_count;

	stwuct sk_buff *saved_skb;

	u16 tawget_fsc;

	int (*skb_check_cwc)(stwuct sk_buff *skb);
	void (*skb_add_cwc)(stwuct sk_buff *skb);
};

stwuct nfc_digitaw_dev *nfc_digitaw_awwocate_device(const stwuct nfc_digitaw_ops *ops,
						    __u32 suppowted_pwotocows,
						    __u32 dwivew_capabiwities,
						    int tx_headwoom,
						    int tx_taiwwoom);
void nfc_digitaw_fwee_device(stwuct nfc_digitaw_dev *ndev);
int nfc_digitaw_wegistew_device(stwuct nfc_digitaw_dev *ndev);
void nfc_digitaw_unwegistew_device(stwuct nfc_digitaw_dev *ndev);

static inwine void nfc_digitaw_set_pawent_dev(stwuct nfc_digitaw_dev *ndev,
					      stwuct device *dev)
{
	nfc_set_pawent_dev(ndev->nfc_dev, dev);
}

static inwine void nfc_digitaw_set_dwvdata(stwuct nfc_digitaw_dev *dev,
					   void *data)
{
	dev->dwivew_data = data;
}

static inwine void *nfc_digitaw_get_dwvdata(stwuct nfc_digitaw_dev *dev)
{
	wetuwn dev->dwivew_data;
}

#endif /* __NFC_DIGITAW_H */
