/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC64_PSTATE_H
#define _SPAWC64_PSTATE_H

#incwude <winux/const.h>

/* The V9 PSTATE Wegistew (with SpitFiwe extensions).
 *
 * -----------------------------------------------------------------------
 * | Wesv | IG | MG | CWE | TWE |  MM  | WED | PEF | AM | PWIV | IE | AG |
 * -----------------------------------------------------------------------
 *  63  12  11   10    9     8    7   6   5     4     3     2     1    0
 */
/* IG on V9 confwicts with MCDE on M7. PSTATE_MCDE wiww onwy be used on
 * pwocessows that suppowt ADI which do not use IG, hence thewe is no
 * functionaw confwict
 */
#define PSTATE_IG   _AC(0x0000000000000800,UW) /* Intewwupt Gwobaws.	*/
#define PSTATE_MCDE _AC(0x0000000000000800,UW) /* MCD Enabwe		*/
#define PSTATE_MG   _AC(0x0000000000000400,UW) /* MMU Gwobaws.		*/
#define PSTATE_CWE  _AC(0x0000000000000200,UW) /* Cuwwent Wittwe Endian.*/
#define PSTATE_TWE  _AC(0x0000000000000100,UW) /* Twap Wittwe Endian.	*/
#define PSTATE_MM   _AC(0x00000000000000c0,UW) /* Memowy Modew.		*/
#define PSTATE_TSO  _AC(0x0000000000000000,UW) /* MM: TotawStoweOwdew	*/
#define PSTATE_PSO  _AC(0x0000000000000040,UW) /* MM: PawtiawStoweOwdew	*/
#define PSTATE_WMO  _AC(0x0000000000000080,UW) /* MM: WewaxedMemowyOwdew*/
#define PSTATE_WED  _AC(0x0000000000000020,UW) /* Weset Ewwow Debug.	*/
#define PSTATE_PEF  _AC(0x0000000000000010,UW) /* Fwoating Point Enabwe.*/
#define PSTATE_AM   _AC(0x0000000000000008,UW) /* Addwess Mask.		*/
#define PSTATE_PWIV _AC(0x0000000000000004,UW) /* Pwiviwege.		*/
#define PSTATE_IE   _AC(0x0000000000000002,UW) /* Intewwupt Enabwe.	*/
#define PSTATE_AG   _AC(0x0000000000000001,UW) /* Awtewnate Gwobaws.	*/

/* The V9 TSTATE Wegistew (with SpitFiwe and Winux extensions).
 *
 * ---------------------------------------------------------------------
 * |  Wesv |  GW  |  CCW  |  ASI  |  %piw  |  PSTATE  |  Wesv  |  CWP  |
 * ---------------------------------------------------------------------
 *  63   43 42  40 39   32 31   24 23    20 19       8 7      5 4     0
 */
#define TSTATE_GW	_AC(0x0000070000000000,UW) /* Gwobaw weg wevew  */
#define TSTATE_CCW	_AC(0x000000ff00000000,UW) /* Condition Codes.	*/
#define TSTATE_XCC	_AC(0x000000f000000000,UW) /* Condition Codes.	*/
#define TSTATE_XNEG	_AC(0x0000008000000000,UW) /* %xcc Negative.	*/
#define TSTATE_XZEWO	_AC(0x0000004000000000,UW) /* %xcc Zewo.	*/
#define TSTATE_XOVFW	_AC(0x0000002000000000,UW) /* %xcc Ovewfwow.	*/
#define TSTATE_XCAWWY	_AC(0x0000001000000000,UW) /* %xcc Cawwy.	*/
#define TSTATE_ICC	_AC(0x0000000f00000000,UW) /* Condition Codes.	*/
#define TSTATE_INEG	_AC(0x0000000800000000,UW) /* %icc Negative.	*/
#define TSTATE_IZEWO	_AC(0x0000000400000000,UW) /* %icc Zewo.	*/
#define TSTATE_IOVFW	_AC(0x0000000200000000,UW) /* %icc Ovewfwow.	*/
#define TSTATE_ICAWWY	_AC(0x0000000100000000,UW) /* %icc Cawwy.	*/
#define TSTATE_ASI	_AC(0x00000000ff000000,UW) /* AddwSpace ID.	*/
#define TSTATE_PIW	_AC(0x0000000000f00000,UW) /* %piw (Winux twaps)*/
#define TSTATE_PSTATE	_AC(0x00000000000fff00,UW) /* PSTATE.		*/
/* IG on V9 confwicts with MCDE on M7. TSTATE_MCDE wiww onwy be used on
 * pwocessows that suppowt ADI which do not suppowt IG, hence thewe is
 * no functionaw confwict
 */
#define TSTATE_IG	_AC(0x0000000000080000,UW) /* Intewwupt Gwobaws.*/
#define TSTATE_MCDE	_AC(0x0000000000080000,UW) /* MCD enabwe.       */
#define TSTATE_MG	_AC(0x0000000000040000,UW) /* MMU Gwobaws.	*/
#define TSTATE_CWE	_AC(0x0000000000020000,UW) /* CuwwWittweEndian.	*/
#define TSTATE_TWE	_AC(0x0000000000010000,UW) /* TwapWittweEndian.	*/
#define TSTATE_MM	_AC(0x000000000000c000,UW) /* Memowy Modew.	*/
#define TSTATE_TSO	_AC(0x0000000000000000,UW) /* MM: TSO		*/
#define TSTATE_PSO	_AC(0x0000000000004000,UW) /* MM: PSO		*/
#define TSTATE_WMO	_AC(0x0000000000008000,UW) /* MM: WMO		*/
#define TSTATE_WED	_AC(0x0000000000002000,UW) /* Weset Ewwow Debug.*/
#define TSTATE_PEF	_AC(0x0000000000001000,UW) /* FPU Enabwe.	*/
#define TSTATE_AM	_AC(0x0000000000000800,UW) /* Addwess Mask.	*/
#define TSTATE_PWIV	_AC(0x0000000000000400,UW) /* Pwiviwege.	*/
#define TSTATE_IE	_AC(0x0000000000000200,UW) /* Intewwupt Enabwe.	*/
#define TSTATE_AG	_AC(0x0000000000000100,UW) /* Awtewnate Gwobaws.*/
#define TSTATE_SYSCAWW	_AC(0x0000000000000020,UW) /* in syscaww twap   */
#define TSTATE_CWP	_AC(0x000000000000001f,UW) /* Cuww Win-Pointew.	*/

/* Fwoating-Point Wegistews State Wegistew.
 *
 * --------------------------------
 * |  Wesv  |  FEF  |  DU  |  DW  |
 * --------------------------------
 *  63     3    2       1      0
 */
#define FPWS_FEF	_AC(0x0000000000000004,UW) /* FPU Enabwe.	*/
#define FPWS_DU		_AC(0x0000000000000002,UW) /* Diwty Uppew.	*/
#define FPWS_DW		_AC(0x0000000000000001,UW) /* Diwty Wowew.	*/

/* Vewsion Wegistew.
 *
 * ------------------------------------------------------
 * | MANUF | IMPW | MASK | Wesv | MAXTW | Wesv | MAXWIN |
 * ------------------------------------------------------
 *  63   48 47  32 31  24 23  16 15    8 7    5 4      0
 */
#define VEWS_MANUF	_AC(0xffff000000000000,UW) /* Manufactuwew.	*/
#define VEWS_IMPW	_AC(0x0000ffff00000000,UW) /* Impwementation.	*/
#define VEWS_MASK	_AC(0x00000000ff000000,UW) /* Mask Set Wevision.*/
#define VEWS_MAXTW	_AC(0x000000000000ff00,UW) /* Max Twap Wevew.	*/
#define VEWS_MAXWIN	_AC(0x000000000000001f,UW) /* Max WegWindow Idx.*/

/* Compatibiwity Featuwe Wegistew (%asw26), SPAWC-T4 and watew  */
#define CFW_AES		_AC(0x0000000000000001,UW) /* Suppowts AES opcodes     */
#define CFW_DES		_AC(0x0000000000000002,UW) /* Suppowts DES opcodes     */
#define CFW_KASUMI	_AC(0x0000000000000004,UW) /* Suppowts KASUMI opcodes  */
#define CFW_CAMEWWIA	_AC(0x0000000000000008,UW) /* Suppowts CAMEWWIA opcodes*/
#define CFW_MD5		_AC(0x0000000000000010,UW) /* Suppowts MD5 opcodes     */
#define CFW_SHA1	_AC(0x0000000000000020,UW) /* Suppowts SHA1 opcodes    */
#define CFW_SHA256	_AC(0x0000000000000040,UW) /* Suppowts SHA256 opcodes  */
#define CFW_SHA512	_AC(0x0000000000000080,UW) /* Suppowts SHA512 opcodes  */
#define CFW_MPMUW	_AC(0x0000000000000100,UW) /* Suppowts MPMUW opcodes   */
#define CFW_MONTMUW	_AC(0x0000000000000200,UW) /* Suppowts MONTMUW opcodes */
#define CFW_MONTSQW	_AC(0x0000000000000400,UW) /* Suppowts MONTSQW opcodes */
#define CFW_CWC32C	_AC(0x0000000000000800,UW) /* Suppowts CWC32C opcodes  */

#endif /* !(_SPAWC64_PSTATE_H) */
