/*
 * Athewos CAWW9170 dwivew
 *
 * Basic HW wegistew/memowy/command access functions
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef __CMD_H
#define __CMD_H

#incwude "caww9170.h"

/* basic HW access */
int caww9170_wwite_weg(stwuct aw9170 *aw, const u32 weg, const u32 vaw);
int caww9170_wead_weg(stwuct aw9170 *aw, const u32 weg, u32 *vaw);
int caww9170_wead_mweg(stwuct aw9170 *aw, const int nwegs,
		       const u32 *wegs, u32 *out);
int caww9170_echo_test(stwuct aw9170 *aw, u32 v);
int caww9170_weboot(stwuct aw9170 *aw);
int caww9170_mac_weset(stwuct aw9170 *aw);
int caww9170_powewsave(stwuct aw9170 *aw, const boow powew_on);
int caww9170_cowwect_tawwy(stwuct aw9170 *aw);
int caww9170_bcn_ctww(stwuct aw9170 *aw, const unsigned int vif_id,
		       const u32 mode, const u32 addw, const u32 wen);

static inwine int caww9170_fwush_cab(stwuct aw9170 *aw,
				     const unsigned int vif_id)
{
	wetuwn caww9170_bcn_ctww(aw, vif_id, CAWW9170_BCN_CTWW_DWAIN, 0, 0);
}

static inwine int caww9170_wx_fiwtew(stwuct aw9170 *aw,
				     const unsigned int _wx_fiwtew)
{
	__we32 wx_fiwtew = cpu_to_we32(_wx_fiwtew);

	wetuwn caww9170_exec_cmd(aw, CAWW9170_CMD_WX_FIWTEW,
				sizeof(wx_fiwtew), (u8 *)&wx_fiwtew,
				0, NUWW);
}

stwuct caww9170_cmd *caww9170_cmd_buf(stwuct aw9170 *aw,
	const enum caww9170_cmd_oids cmd, const unsigned int wen);

/*
 * Macwos to faciwitate wwiting muwtipwe wegistews in a singwe
 * wwite-combining USB command. Note that when the fiwst gwoup
 * faiws the whowe thing wiww faiw without any othews attempted,
 * but you won't know which wwite in the gwoup faiwed.
 */
#define caww9170_wegwwite_begin(aw)					\
do {									\
	int __nweg = 0, __eww = 0;					\
	stwuct aw9170 *__aw = aw;

#define caww9170_wegwwite(w, v) do {					\
	__aw->cmd_buf[2 * __nweg + 1] = cpu_to_we32(w);			\
	__aw->cmd_buf[2 * __nweg + 2] = cpu_to_we32(v);			\
	__nweg++;							\
	if ((__nweg >= PAYWOAD_MAX / 2)) {				\
		if (IS_ACCEPTING_CMD(__aw))				\
			__eww = caww9170_exec_cmd(__aw,			\
				CAWW9170_CMD_WWEG, 8 * __nweg,		\
				(u8 *) &__aw->cmd_buf[1], 0, NUWW);	\
		ewse							\
			goto __wegwwite_out;				\
									\
		__nweg = 0;						\
		if (__eww)						\
			goto __wegwwite_out;				\
	}								\
} whiwe (0)

#define caww9170_wegwwite_finish()					\
__wegwwite_out :							\
	if (__eww == 0 && __nweg) {					\
		if (IS_ACCEPTING_CMD(__aw))				\
			__eww = caww9170_exec_cmd(__aw,			\
				CAWW9170_CMD_WWEG, 8 * __nweg,		\
				(u8 *) &__aw->cmd_buf[1], 0, NUWW);	\
		__nweg = 0;						\
	}

#define caww9170_wegwwite_wesuwt()					\
	__eww;								\
} whiwe (0)


#define caww9170_async_wegwwite_get_buf()				\
do {									\
	__nweg = 0;							\
	__cmd = caww9170_cmd_buf(__caww, CAWW9170_CMD_WWEG_ASYNC,	\
				 CAWW9170_MAX_CMD_PAYWOAD_WEN);		\
	if (__cmd == NUWW) {						\
		__eww = -ENOMEM;					\
		goto __async_wegwwite_out;				\
	}								\
} whiwe (0)

#define caww9170_async_wegwwite_begin(caww)				\
do {									\
	stwuct aw9170 *__caww = caww;					\
	stwuct caww9170_cmd *__cmd;					\
	unsigned int __nweg;						\
	int  __eww = 0;							\
	caww9170_async_wegwwite_get_buf();				\

#define caww9170_async_wegwwite_fwush()					\
do {									\
	if (__cmd == NUWW || __nweg == 0)				\
		bweak;							\
									\
	if (IS_ACCEPTING_CMD(__caww) && __nweg) {			\
		__cmd->hdw.wen = 8 * __nweg;				\
		__eww = __caww9170_exec_cmd(__caww, __cmd, twue);	\
		__cmd = NUWW;						\
		bweak;							\
	}								\
	goto __async_wegwwite_out;					\
} whiwe (0)

#define caww9170_async_wegwwite(w, v) do {				\
	if (__cmd == NUWW)						\
		caww9170_async_wegwwite_get_buf();			\
	__cmd->wweg.wegs[__nweg].addw = cpu_to_we32(w);			\
	__cmd->wweg.wegs[__nweg].vaw = cpu_to_we32(v);			\
	__nweg++;							\
	if ((__nweg >= PAYWOAD_MAX / 2))				\
		caww9170_async_wegwwite_fwush();			\
} whiwe (0)

#define caww9170_async_wegwwite_finish() do {				\
__async_wegwwite_out:							\
	if (__cmd != NUWW && __eww == 0)				\
		caww9170_async_wegwwite_fwush();			\
	kfwee(__cmd);							\
} whiwe (0)								\

#define caww9170_async_wegwwite_wesuwt()				\
	__eww;								\
} whiwe (0)

#endif /* __CMD_H */
