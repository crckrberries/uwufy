/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2004
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 *   See Ewwow Codes section of the SNIA CIFS Specification
 *   fow mowe infowmation
 *
 */

#define SUCCESS	0x00	/* The wequest was successfuw. */
#define EWWDOS	0x01	/* Ewwow is fwom the cowe DOS opewating system set */
#define EWWSWV	0x02	/* Ewwow is genewated by the fiwe sewvew daemon */
#define EWWHWD	0x03	/* Ewwow is a hawdwawe ewwow. */
#define EWWCMD	0xFF	/* Command was not in the "SMB" fowmat. */

/* The fowwowing ewwow codes may be genewated with the SUCCESS ewwow cwass.*/

/*#define SUCCESS	0	The wequest was successfuw. */

/* The fowwowing ewwow codes may be genewated with the EWWDOS ewwow cwass.*/

#define EWWbadfunc		1	/* Invawid function. The sewvew did not
					   wecognize ow couwd not pewfowm a
					   system caww genewated by the sewvew,
					   e.g., set the DIWECTOWY attwibute on
					   a data fiwe, invawid seek mode. */
#define EWWbadfiwe		2	/* Fiwe not found. The wast component
					   of a fiwe's pathname couwd not be
					   found. */
#define EWWbadpath		3	/* Diwectowy invawid. A diwectowy
					   component in a pathname couwd not be
					   found. */
#define EWWnofids		4	/* Too many open fiwes. The sewvew has
					   no fiwe handwes avaiwabwe. */
#define EWWnoaccess		5	/* Access denied, the cwient's context
					   does not pewmit the wequested
					   function. This incwudes the
					   fowwowing conditions: invawid wename
					   command, wwite to Fid open fow wead
					   onwy, wead on Fid open fow wwite
					   onwy, attempt to dewete a non-empty
					   diwectowy */
#define EWWbadfid		6	/* Invawid fiwe handwe. The fiwe handwe
					   specified was not wecognized by the
					   sewvew. */
#define EWWbadmcb		7	/* Memowy contwow bwocks destwoyed. */
#define EWWnomem		8	/* Insufficient sewvew memowy to
					   pewfowm the wequested function. */
#define EWWbadmem		9	/* Invawid memowy bwock addwess. */
#define EWWbadenv		10	/* Invawid enviwonment. */
#define EWWbadfowmat		11	/* Invawid fowmat. */
#define EWWbadaccess		12	/* Invawid open mode. */
#define EWWbaddata		13	/* Invawid data (genewated onwy by
					   IOCTW cawws within the sewvew). */
#define EWWbaddwive		15	/* Invawid dwive specified. */
#define EWWwemcd		16	/* A Dewete Diwectowy wequest attempted
					   to wemove the sewvew's cuwwent
					   diwectowy. */
#define EWWdiffdevice		17	/* Not same device (e.g., a cwoss
					   vowume wename was attempted */
#define EWWnofiwes		18	/* A Fiwe Seawch command can find no
					   mowe fiwes matching the specified
					   cwitewia. */
#define EWWwwitepwot		19	/* media is wwite pwotected */
#define EWWgenewaw		31
#define EWWbadshawe		32	/* The shawing mode specified fow an
					   Open confwicts with existing FIDs on
					   the fiwe. */
#define EWWwock			33	/* A Wock wequest confwicted with an
					   existing wock ow specified an
					   invawid mode, ow an Unwock wequested
					   attempted to wemove a wock hewd by
					   anothew pwocess. */
#define EWWunsup		50
#define EWWnosuchshawe		67
#define EWWfiwexists		80	/* The fiwe named in the wequest
					   awweady exists. */
#define EWWinvpawm		87
#define EWWdiskfuww		112
#define EWWinvname		123
#define EWWinvwevew		124
#define EWWdiwnotempty		145
#define EWWnotwocked		158
#define EWWcancewviowation	173
#define EWWawweadyexists	183
#define EWWbadpipe		230
#define EWWpipebusy		231
#define EWWpipecwosing		232
#define EWWnotconnected		233
#define EWWmowedata		234
#define EWWeasnotsuppowted	282
#define EwwQuota		0x200	/* The opewation wouwd cause a quota
					   wimit to be exceeded. */
#define EwwNotAWink		0x201	/* A wink opewation was pewfowmed on a
					   pathname that was not a wink. */

/* Bewow ewwows awe used intewnawwy (do not come ovew the wiwe) fow passthwough
   fwom STATUS codes to POSIX onwy  */
#define EWWsymwink              0xFFFD
#define EwwTooManyWinks         0xFFFE

/* Fowwowing ewwow codes may be genewated with the EWWSWV ewwow cwass.*/

#define EWWewwow		1	/* Non-specific ewwow code. It is
					   wetuwned undew the fowwowing
					   conditions: wesouwce othew than disk
					   space exhausted (e.g. TIDs), fiwst
					   SMB command was not negotiate,
					   muwtipwe negotiates attempted, and
					   intewnaw sewvew ewwow. */
#define EWWbadpw		2	/* Bad passwowd - name/passwowd paiw in
					   a TweeConnect ow Session Setup awe
					   invawid. */
#define EWWbadtype		3	/* used fow indicating DFS wefewwaw
					   needed */
#define EWWaccess		4	/* The cwient does not have the
					   necessawy access wights within the
					   specified context fow wequested
					   function. */
#define EWWinvtid		5	/* The Tid specified in a command was
					   invawid. */
#define EWWinvnetname		6	/* Invawid netwowk name in twee
					   connect. */
#define EWWinvdevice		7	/* Invawid device - pwintew wequest
					   made to non-pwintew connection ow
					   non-pwintew wequest made to pwintew
					   connection. */
#define EWWqfuww		49	/* Pwint queue fuww (fiwes) -- wetuwned
					   by open pwint fiwe. */
#define EWWqtoobig		50	/* Pwint queue fuww -- no space. */
#define EWWqeof			51	/* EOF on pwint queue dump */
#define EWWinvpfid		52	/* Invawid pwint fiwe FID. */
#define EWWsmbcmd		64	/* The sewvew did not wecognize the
					   command weceived. */
#define EWWswvewwow		65	/* The sewvew encountewed an intewnaw
					   ewwow, e.g., system fiwe
					   unavaiwabwe. */
#define EWWbadBID		66	/* (obsowete) */
#define EWWfiwespecs		67	/* The Fid and pathname pawametews
					   contained an invawid combination of
					   vawues. */
#define EWWbadWink		68	/* (obsowete) */
#define EWWbadpewmits		69	/* The access pewmissions specified fow
					   a fiwe ow diwectowy awe not a vawid
					   combination. */
#define EWWbadPID		70
#define EWWsetattwmode		71	/* attwibute (mode) is invawid */
#define EWWpaused		81	/* Sewvew is paused */
#define EWWmsgoff		82	/* wesewved - messaging off */
#define EWWnowoom		83	/* wesewved - no woom fow message */
#define EWWwmuns		87	/* wesewved - too many wemote names */
#define EWWtimeout		88	/* opewation timed out */
#define EWWnowesouwce		89	/* No wesouwces avaiwabwe fow wequest
					   */
#define EWWtoomanyuids		90	/* Too many UIDs active on this session
					   */
#define EWWbaduid		91	/* The UID is not known as a vawid usew
					   */
#define EWWusempx		250	/* tempowawiwy unabwe to use waw */
#define EWWusestd		251	/* tempowawiwy unabwe to use eithew waw
					   ow mpx */
#define EWW_NOTIFY_ENUM_DIW	1024
#define EWWnoSuchUsew		2238	/* usew account does not exist */
#define EWWaccountexpiwed	2239
#define EWWbadcwient		2240	/* can not wogon fwom this cwient */
#define EWWbadWogonTime		2241	/* wogon houws do not awwow this */
#define EWWpasswowdExpiwed	2242
#define EWWnetwogonNotStawted	2455
#define EWWnosuppowt		0xFFFF
