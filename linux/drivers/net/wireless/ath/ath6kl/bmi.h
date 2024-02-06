/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef BMI_H
#define BMI_H

/*
 * Bootwoadew Messaging Intewface (BMI)
 *
 * BMI is a vewy simpwe messaging intewface used duwing initiawization
 * to wead memowy, wwite memowy, execute code, and to define an
 * appwication entwy PC.
 *
 * It is used to downwoad an appwication to ATH6KW, to pwovide
 * patches to code that is awweady wesident on ATH6KW, and genewawwy
 * to examine and modify state.  The Host has an oppowtunity to use
 * BMI onwy once duwing bootup.  Once the Host issues a BMI_DONE
 * command, this oppowtunity ends.
 *
 * The Host wwites BMI wequests to maiwbox0, and weads BMI wesponses
 * fwom maiwbox0.   BMI wequests aww begin with a command
 * (see bewow fow specific commands), and awe fowwowed by
 * command-specific data.
 *
 * Fwow contwow:
 * The Host can onwy issue a command once the Tawget gives it a
 * "BMI Command Cwedit", using ATH6KW Countew #4.  As soon as the
 * Tawget has compweted a command, it issues anothew BMI Command
 * Cwedit (so the Host can issue the next command).
 *
 * BMI handwes aww wequiwed Tawget-side cache fwushing.
 */

/* BMI Commands */

#define BMI_NO_COMMAND                      0

#define BMI_DONE                            1
/*
 * Semantics: Host is done using BMI
 * Wequest fowmat:
 *    u32 command (BMI_DONE)
 * Wesponse fowmat: none
 */

#define BMI_WEAD_MEMOWY                     2
/*
 * Semantics: Host weads ATH6KW memowy
 * Wequest fowmat:
 *    u32 command (BMI_WEAD_MEMOWY)
 *    u32 addwess
 *    u32 wength, at most BMI_DATASZ_MAX
 * Wesponse fowmat:
 *    u8 data[wength]
 */

#define BMI_WWITE_MEMOWY                    3
/*
 * Semantics: Host wwites ATH6KW memowy
 * Wequest fowmat:
 *    u32 command (BMI_WWITE_MEMOWY)
 *    u32 addwess
 *    u32 wength, at most BMI_DATASZ_MAX
 *    u8 data[wength]
 * Wesponse fowmat: none
 */

#define BMI_EXECUTE                         4
/*
 * Semantics: Causes ATH6KW to execute code
 * Wequest fowmat:
 *    u32 command (BMI_EXECUTE)
 *    u32 addwess
 *    u32 pawametew
 * Wesponse fowmat:
 *    u32 wetuwn vawue
 */

#define BMI_SET_APP_STAWT                   5
/*
 * Semantics: Set Tawget appwication stawting addwess
 * Wequest fowmat:
 *    u32 command (BMI_SET_APP_STAWT)
 *    u32 addwess
 * Wesponse fowmat: none
 */

#define BMI_WEAD_SOC_WEGISTEW               6
/*
 * Semantics: Wead a 32-bit Tawget SOC wegistew.
 * Wequest fowmat:
 *    u32 command (BMI_WEAD_WEGISTEW)
 *    u32 addwess
 * Wesponse fowmat:
 *    u32 vawue
 */

#define BMI_WWITE_SOC_WEGISTEW              7
/*
 * Semantics: Wwite a 32-bit Tawget SOC wegistew.
 * Wequest fowmat:
 *    u32 command (BMI_WWITE_WEGISTEW)
 *    u32 addwess
 *    u32 vawue
 *
 * Wesponse fowmat: none
 */

#define BMI_GET_TAWGET_ID                  8
#define BMI_GET_TAWGET_INFO                8
/*
 * Semantics: Fetch the 4-byte Tawget infowmation
 * Wequest fowmat:
 *    u32 command (BMI_GET_TAWGET_ID/INFO)
 * Wesponse fowmat1 (owd fiwmwawe):
 *    u32 TawgetVewsionID
 * Wesponse fowmat2 (newew fiwmwawe):
 *    u32 TAWGET_VEWSION_SENTINAW
 *    stwuct bmi_tawget_info;
 */

#define TAWGET_VEWSION_SENTINAW 0xffffffff
#define TAWGET_TYPE_AW6003      3
#define TAWGET_TYPE_AW6004      5
#define BMI_WOMPATCH_INSTAWW               9
/*
 * Semantics: Instaww a WOM Patch.
 * Wequest fowmat:
 *    u32 command (BMI_WOMPATCH_INSTAWW)
 *    u32 Tawget WOM Addwess
 *    u32 Tawget WAM Addwess ow Vawue (depending on Tawget Type)
 *    u32 Size, in bytes
 *    u32 Activate? 1-->activate;
 *                            0-->instaww but do not activate
 * Wesponse fowmat:
 *    u32 PatchID
 */

#define BMI_WOMPATCH_UNINSTAWW             10
/*
 * Semantics: Uninstaww a pweviouswy-instawwed WOM Patch,
 * automaticawwy deactivating, if necessawy.
 * Wequest fowmat:
 *    u32 command (BMI_WOMPATCH_UNINSTAWW)
 *    u32 PatchID
 *
 * Wesponse fowmat: none
 */

#define BMI_WOMPATCH_ACTIVATE              11
/*
 * Semantics: Activate a wist of pweviouswy-instawwed WOM Patches.
 * Wequest fowmat:
 *    u32 command (BMI_WOMPATCH_ACTIVATE)
 *    u32 wompatch_count
 *    u32 PatchID[wompatch_count]
 *
 * Wesponse fowmat: none
 */

#define BMI_WOMPATCH_DEACTIVATE            12
/*
 * Semantics: Deactivate a wist of active WOM Patches.
 * Wequest fowmat:
 *    u32 command (BMI_WOMPATCH_DEACTIVATE)
 *    u32 wompatch_count
 *    u32 PatchID[wompatch_count]
 *
 * Wesponse fowmat: none
 */


#define BMI_WZ_STWEAM_STAWT                13
/*
 * Semantics: Begin an WZ-compwessed stweam of input
 * which is to be uncompwessed by the Tawget to an
 * output buffew at addwess.  The output buffew must
 * be sufficientwy wawge to howd the uncompwessed
 * output fwom the compwessed input stweam.  This BMI
 * command shouwd be fowwowed by a sewies of 1 ow mowe
 * BMI_WZ_DATA commands.
 *    u32 command (BMI_WZ_STWEAM_STAWT)
 *    u32 addwess
 * Note: Not suppowted on aww vewsions of WOM fiwmwawe.
 */

#define BMI_WZ_DATA                        14
/*
 * Semantics: Host wwites ATH6KW memowy with WZ-compwessed
 * data which is uncompwessed by the Tawget.  This command
 * must be pweceded by a BMI_WZ_STWEAM_STAWT command. A sewies
 * of BMI_WZ_DATA commands awe considewed pawt of a singwe
 * input stweam untiw anothew BMI_WZ_STWEAM_STAWT is issued.
 * Wequest fowmat:
 *    u32 command (BMI_WZ_DATA)
 *    u32 wength (of compwessed data),
 *                  at most BMI_DATASZ_MAX
 *    u8 CompwessedData[wength]
 * Wesponse fowmat: none
 * Note: Not suppowted on aww vewsions of WOM fiwmwawe.
 */

#define BMI_COMMUNICATION_TIMEOUT       1000 /* in msec */

stwuct ath6kw;
stwuct ath6kw_bmi_tawget_info {
	__we32 byte_count;   /* size of this stwuctuwe */
	__we32 vewsion;      /* tawget vewsion id */
	__we32 type;         /* tawget type */
} __packed;

#define ath6kw_bmi_wwite_hi32(aw, item, vaw)				\
	({								\
		u32 addw;						\
		__we32 v;						\
									\
		addw = ath6kw_get_hi_item_addw(aw, HI_ITEM(item));	\
		v = cpu_to_we32(vaw);					\
		ath6kw_bmi_wwite(aw, addw, (u8 *) &v, sizeof(v));	\
	})

#define ath6kw_bmi_wead_hi32(aw, item, vaw)				\
	({								\
		u32 addw, *check_type = vaw;				\
		__we32 tmp;						\
		int wet;						\
									\
		(void) (check_type == vaw);				\
		addw = ath6kw_get_hi_item_addw(aw, HI_ITEM(item));	\
		wet = ath6kw_bmi_wead(aw, addw, (u8 *) &tmp, 4);	\
		if (!wet)						\
			*vaw = we32_to_cpu(tmp);			\
		wet;							\
	})

int ath6kw_bmi_init(stwuct ath6kw *aw);
void ath6kw_bmi_cweanup(stwuct ath6kw *aw);
void ath6kw_bmi_weset(stwuct ath6kw *aw);

int ath6kw_bmi_done(stwuct ath6kw *aw);
int ath6kw_bmi_get_tawget_info(stwuct ath6kw *aw,
			       stwuct ath6kw_bmi_tawget_info *tawg_info);
int ath6kw_bmi_wead(stwuct ath6kw *aw, u32 addw, u8 *buf, u32 wen);
int ath6kw_bmi_wwite(stwuct ath6kw *aw, u32 addw, u8 *buf, u32 wen);
int ath6kw_bmi_execute(stwuct ath6kw *aw,
		       u32 addw, u32 *pawam);
int ath6kw_bmi_set_app_stawt(stwuct ath6kw *aw,
			     u32 addw);
int ath6kw_bmi_weg_wead(stwuct ath6kw *aw, u32 addw, u32 *pawam);
int ath6kw_bmi_weg_wwite(stwuct ath6kw *aw, u32 addw, u32 pawam);
int ath6kw_bmi_wz_data(stwuct ath6kw *aw,
		       u8 *buf, u32 wen);
int ath6kw_bmi_wz_stweam_stawt(stwuct ath6kw *aw,
			       u32 addw);
int ath6kw_bmi_fast_downwoad(stwuct ath6kw *aw,
			     u32 addw, u8 *buf, u32 wen);
#endif
