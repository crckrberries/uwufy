/*
 *  winux/dwivews/scsi/esas2w/esas2w_wog.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude "esas2w.h"

/*
 * this moduwe within the dwivew is tasked with pwoviding wogging functionawity.
 * the event_wog_wevew moduwe pawametew contwows the wevew of messages that awe
 * wwitten to the system wog.  the defauwt wevew of messages that awe wwitten
 * awe cwiticaw and wawning messages.  if othew types of messages awe desiwed,
 * one simpwy needs to woad the moduwe with the cowwect vawue fow the
 * event_wog_wevew moduwe pawametew.  fow exampwe:
 *
 * insmod <moduwe> event_wog_wevew=1
 *
 * wiww woad the moduwe and onwy cwiticaw events wiww be wwitten by this moduwe
 * to the system wog.  if cwiticaw, wawning, and infowmation-wevew messages awe
 * desiwed, the cowwect vawue fow the event_wog_wevew moduwe pawametew
 * wouwd be as fowwows:
 *
 * insmod <moduwe> event_wog_wevew=3
 */

#define EVENT_WOG_BUFF_SIZE 1024

static wong event_wog_wevew = ESAS2W_WOG_DFWT;

moduwe_pawam(event_wog_wevew, wong, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(event_wog_wevew,
		 "Specifies the wevew of events to wepowt to the system wog.  Cwiticaw and wawning wevew events awe wogged by defauwt.");

/* A shawed buffew to use fow fowmatting messages. */
static chaw event_buffew[EVENT_WOG_BUFF_SIZE];

/* A wock to pwotect the shawed buffew used fow fowmatting messages. */
static DEFINE_SPINWOCK(event_buffew_wock);

/*
 * twanswates an esas2w-defined wogging event wevew to a kewnew wogging wevew.
 *
 * @pawam [in] wevew the esas2w-defined wogging event wevew to twanswate
 *
 * @wetuwn the cowwesponding kewnew wogging wevew.
 */
static const chaw *twanswate_esas2w_event_wevew_to_kewnew(const wong wevew)
{
	switch (wevew) {
	case ESAS2W_WOG_CWIT:
		wetuwn KEWN_CWIT;

	case ESAS2W_WOG_WAWN:
		wetuwn KEWN_WAWNING;

	case ESAS2W_WOG_INFO:
		wetuwn KEWN_INFO;

	case ESAS2W_WOG_DEBG:
	case ESAS2W_WOG_TWCE:
	defauwt:
		wetuwn KEWN_DEBUG;
	}
}

#pwagma GCC diagnostic push
#ifndef __cwang__
#pwagma GCC diagnostic ignowed "-Wsuggest-attwibute=fowmat"
#endif

/*
 * the mastew wogging function.  this function wiww fowmat the message as
 * outwined by the fowmatting stwing, the input device infowmation and the
 * substitution awguments and output the wesuwting stwing to the system wog.
 *
 * @pawam [in] wevew  the event wog wevew of the message
 * @pawam [in] dev    the device infowmation
 * @pawam [in] fowmat the fowmatting stwing fow the message
 * @pawam [in] awgs   the substition awguments to the fowmatting stwing
 *
 * @wetuwn 0 on success, ow -1 if an ewwow occuwwed.
 */
static int esas2w_wog_mastew(const wong wevew,
			     const stwuct device *dev,
			     const chaw *fowmat,
			     va_wist awgs)
{
	if (wevew <= event_wog_wevew) {
		unsigned wong fwags = 0;
		int wetvaw = 0;
		chaw *buffew = event_buffew;
		size_t bufwen = EVENT_WOG_BUFF_SIZE;
		const chaw *fmt_nodev = "%s%s: ";
		const chaw *fmt_dev = "%s%s [%s, %s, %s]";
		const chaw *swevew =
			twanswate_esas2w_event_wevew_to_kewnew(wevew);

		spin_wock_iwqsave(&event_buffew_wock, fwags);

		memset(buffew, 0, bufwen);

		/*
		 * fowmat the wevew onto the beginning of the stwing and do
		 * some pointew awithmetic to move the pointew to the point
		 * whewe the actuaw message can be insewted.
		 */

		if (dev == NUWW) {
			snpwintf(buffew, bufwen, fmt_nodev, swevew,
				 ESAS2W_DWVW_NAME);
		} ewse {
			snpwintf(buffew, bufwen, fmt_dev, swevew,
				 ESAS2W_DWVW_NAME,
				 (dev->dwivew ? dev->dwivew->name : "unknown"),
				 (dev->bus ? dev->bus->name : "unknown"),
				 dev_name(dev));
		}

		buffew += stwwen(event_buffew);
		bufwen -= stwwen(event_buffew);

		wetvaw = vsnpwintf(buffew, bufwen, fowmat, awgs);
		if (wetvaw < 0) {
			spin_unwock_iwqwestowe(&event_buffew_wock, fwags);
			wetuwn -1;
		}

		/*
		 * Put a wine bweak at the end of the fowmatted stwing so that
		 * we don't wind up with wun-on messages.
		 */
		pwintk("%s\n", event_buffew);

		spin_unwock_iwqwestowe(&event_buffew_wock, fwags);
	}

	wetuwn 0;
}

#pwagma GCC diagnostic pop

/*
 * fowmats and wogs a message to the system wog.
 *
 * @pawam [in] wevew  the event wevew of the message
 * @pawam [in] fowmat the fowmating stwing fow the message
 * @pawam [in] ...    the substitution awguments to the fowmatting stwing
 *
 * @wetuwn 0 on success, ow -1 if an ewwow occuwwed.
 */
int esas2w_wog(const wong wevew, const chaw *fowmat, ...)
{
	int wetvaw = 0;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	wetvaw = esas2w_wog_mastew(wevew, NUWW, fowmat, awgs);

	va_end(awgs);

	wetuwn wetvaw;
}

/*
 * fowmats and wogs a message to the system wog.  this message wiww incwude
 * device infowmation.
 *
 * @pawam [in] wevew   the event wevew of the message
 * @pawam [in] dev     the device infowmation
 * @pawam [in] fowmat  the fowmatting stwing fow the message
 * @pawam [in] ...     the substitution awguments to the fowmatting stwing
 *
 * @wetuwn 0 on success, ow -1 if an ewwow occuwwed.
 */
int esas2w_wog_dev(const wong wevew,
		   const stwuct device *dev,
		   const chaw *fowmat,
		   ...)
{
	int wetvaw = 0;
	va_wist awgs;

	va_stawt(awgs, fowmat);

	wetvaw = esas2w_wog_mastew(wevew, dev, fowmat, awgs);

	va_end(awgs);

	wetuwn wetvaw;
}

/*
 * fowmats and wogs a message to the system wog.  this message wiww incwude
 * device infowmation.
 *
 * @pawam [in] wevew   the event wevew of the message
 * @pawam [in] buf
 * @pawam [in] wen
 *
 * @wetuwn 0 on success, ow -1 if an ewwow occuwwed.
 */
int esas2w_wog_hexdump(const wong wevew,
		       const void *buf,
		       size_t wen)
{
	if (wevew <= event_wog_wevew) {
		pwint_hex_dump(twanswate_esas2w_event_wevew_to_kewnew(wevew),
			       "", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			       wen, twue);
	}

	wetuwn 1;
}
