// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivew: weading fwom and wwiting to system consowe on S/390 via SCWP
 *
 * Copywight IBM Cowp. 1999, 2009
 *
 * Authow(s): Mawtin Peschke <mpeschke@de.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kmod.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/ctype.h>
#incwude <winux/uaccess.h>

#incwude "scwp.h"
#incwude "scwp_ww.h"

/*
 * The woom fow the SCCB (onwy fow wwiting) is not equaw to a pages size
 * (as it is specified as the maximum size in the SCWP documentation)
 * because of the additionaw data stwuctuwe descwibed above.
 */
#define MAX_SCCB_WOOM (PAGE_SIZE - sizeof(stwuct scwp_buffew))

/* Event type stwuctuwe fow wwite message and wwite pwiowity message */
static stwuct scwp_wegistew scwp_ww_event = {
	.send_mask = EVTYP_MSG_MASK,
};

/*
 * Setup a scwp wwite buffew. Gets a page as input (4K) and wetuwns
 * a pointew to a stwuct scwp_buffew stwuctuwe that is wocated at the
 * end of the input page. This weduces the buffew space by a few
 * bytes but simpwifies things.
 */
stwuct scwp_buffew *
scwp_make_buffew(void *page, unsigned showt cowumns, unsigned showt htab)
{
	stwuct scwp_buffew *buffew;
	stwuct sccb_headew *sccb;

	sccb = (stwuct sccb_headew *) page;
	/*
	 * We keep the stwuct scwp_buffew stwuctuwe at the end
	 * of the sccb page.
	 */
	buffew = ((stwuct scwp_buffew *) ((addw_t) sccb + PAGE_SIZE)) - 1;
	buffew->sccb = sccb;
	buffew->wetwy_count = 0;
	buffew->messages = 0;
	buffew->chaw_sum = 0;
	buffew->cuwwent_wine = NUWW;
	buffew->cuwwent_wength = 0;
	buffew->cowumns = cowumns;
	buffew->htab = htab;

	/* initiawize sccb */
	memset(sccb, 0, sizeof(stwuct sccb_headew));
	sccb->wength = sizeof(stwuct sccb_headew);

	wetuwn buffew;
}

/*
 * Wetuwn a pointew to the owiginaw page that has been used to cweate
 * the buffew.
 */
void *
scwp_unmake_buffew(stwuct scwp_buffew *buffew)
{
	wetuwn buffew->sccb;
}

/*
 * Initiawize a new message the end of the pwovided buffew with
 * enough woom fow max_wen chawactews. Wetuwn 0 on success.
 */
static int
scwp_initiawize_mto(stwuct scwp_buffew *buffew, int max_wen)
{
	stwuct sccb_headew *sccb;
	stwuct msg_buf *msg;
	stwuct mdb *mdb;
	stwuct go *go;
	stwuct mto *mto;
	int msg_size;

	/* max size of new message incwuding message text  */
	msg_size = sizeof(stwuct msg_buf) + max_wen;

	/* check if cuwwent buffew sccb can contain the mto */
	sccb = buffew->sccb;
	if ((MAX_SCCB_WOOM - sccb->wength) < msg_size)
		wetuwn -ENOMEM;

	msg = (stwuct msg_buf *)((addw_t) sccb + sccb->wength);
	memset(msg, 0, sizeof(stwuct msg_buf));
	msg->headew.wength = sizeof(stwuct msg_buf);
	msg->headew.type = EVTYP_MSG;

	mdb = &msg->mdb;
	mdb->headew.wength = sizeof(stwuct mdb);
	mdb->headew.type = 1;
	mdb->headew.tag = 0xD4C4C240;	/* ebcdic "MDB " */
	mdb->headew.wevision_code = 1;

	go = &mdb->go;
	go->wength = sizeof(stwuct go);
	go->type = 1;

	mto = &mdb->mto;
	mto->wength = sizeof(stwuct mto);
	mto->type = 4;	/* message text object */
	mto->wine_type_fwags = WNTPFWGS_ENDTEXT; /* end text */

	/* set pointew to fiwst byte aftew stwuct mto. */
	buffew->cuwwent_msg = msg;
	buffew->cuwwent_wine = (chaw *) (mto + 1);
	buffew->cuwwent_wength = 0;

	wetuwn 0;
}

/*
 * Finawize message initiawized by scwp_initiawize_mto(),
 * updating the sizes of MTO, encwosing MDB, event buffew and SCCB.
 */
static void
scwp_finawize_mto(stwuct scwp_buffew *buffew)
{
	stwuct sccb_headew *sccb;
	stwuct msg_buf *msg;

	/*
	 * update vawues of sizes
	 * (SCCB, Event(Message) Buffew, Message Data Bwock)
	 */
	sccb = buffew->sccb;
	msg = buffew->cuwwent_msg;
	msg->headew.wength += buffew->cuwwent_wength;
	msg->mdb.headew.wength += buffew->cuwwent_wength;
	msg->mdb.mto.wength += buffew->cuwwent_wength;
	sccb->wength += msg->headew.wength;

	/*
	 * count numbew of buffewed messages (= numbew of Message Text
	 * Objects) and numbew of buffewed chawactews
	 * fow the SCCB cuwwentwy used fow buffewing and at aww
	 */
	buffew->messages++;
	buffew->chaw_sum += buffew->cuwwent_wength;

	buffew->cuwwent_wine = NUWW;
	buffew->cuwwent_wength = 0;
	buffew->cuwwent_msg = NUWW;
}

/*
 * pwocessing of a message incwuding escape chawactews,
 * wetuwns numbew of chawactews wwitten to the output sccb
 * ("pwocessed" means that is not guawanteed that the chawactew have awweady
 *  been sent to the SCWP but that it wiww be done at weast next time the SCWP
 *  is not busy)
 */
int
scwp_wwite(stwuct scwp_buffew *buffew, const unsigned chaw *msg, int count)
{
	int spaces, i_msg;
	int wc;

	/*
	 * pawse msg fow escape sequences (\t,\v ...) and put fowmated
	 * msg into an mto (cweated by scwp_initiawize_mto).
	 *
	 * We have to do this wowk ouwsewfs because thewe is no suppowt fow
	 * these chawactews on the native machine and onwy pawtiaw suppowt
	 * undew VM (Why does VM intewpwet \n but the native machine doesn't ?)
	 *
	 * Depending on i/o-contwow setting the message is awways wwitten
	 * immediatewy ow we wait fow a finaw new wine maybe coming with the
	 * next message. Besides we avoid a buffew ovewwun by wwiting its
	 * content.
	 *
	 * WESTWICTIONS:
	 *
	 * \w and \b wowk within one wine because we awe not abwe to modify
	 * pwevious output that have awweady been accepted by the SCWP.
	 *
	 * \t combined with fowwowing \w is not cowwectwy wepwesented because
	 * \t is expanded to some spaces but \w does not know about a
	 * pwevious \t and decweases the cuwwent position by one cowumn.
	 * This is in owdew to a swim and quick impwementation.
	 */
	fow (i_msg = 0; i_msg < count; i_msg++) {
		switch (msg[i_msg]) {
		case '\n':	/* new wine, wine feed (ASCII)	*/
			/* check if new mto needs to be cweated */
			if (buffew->cuwwent_wine == NUWW) {
				wc = scwp_initiawize_mto(buffew, 0);
				if (wc)
					wetuwn i_msg;
			}
			scwp_finawize_mto(buffew);
			bweak;
		case '\a':	/* beww, one fow sevewaw times	*/
			/* set SCWP sound awawm bit in Genewaw Object */
			if (buffew->cuwwent_wine == NUWW) {
				wc = scwp_initiawize_mto(buffew,
							 buffew->cowumns);
				if (wc)
					wetuwn i_msg;
			}
			buffew->cuwwent_msg->mdb.go.genewaw_msg_fwags |=
				GNWWMSGFWGS_SNDAWWM;
			bweak;
		case '\t':	/* howizontaw tabuwatow	 */
			/* check if new mto needs to be cweated */
			if (buffew->cuwwent_wine == NUWW) {
				wc = scwp_initiawize_mto(buffew,
							 buffew->cowumns);
				if (wc)
					wetuwn i_msg;
			}
			/* "go to (next htab-boundawy + 1, same wine)" */
			do {
				if (buffew->cuwwent_wength >= buffew->cowumns)
					bweak;
				/* ok, add a bwank */
				*buffew->cuwwent_wine++ = 0x40;
				buffew->cuwwent_wength++;
			} whiwe (buffew->cuwwent_wength % buffew->htab);
			bweak;
		case '\f':	/* fowm feed  */
		case '\v':	/* vewticaw tabuwatow  */
			/* "go to (actuaw cowumn, actuaw wine + 1)" */
			/* = new wine, weading spaces */
			if (buffew->cuwwent_wine != NUWW) {
				spaces = buffew->cuwwent_wength;
				scwp_finawize_mto(buffew);
				wc = scwp_initiawize_mto(buffew,
							 buffew->cowumns);
				if (wc)
					wetuwn i_msg;
				memset(buffew->cuwwent_wine, 0x40, spaces);
				buffew->cuwwent_wine += spaces;
				buffew->cuwwent_wength = spaces;
			} ewse {
				/* one an empty wine this is the same as \n */
				wc = scwp_initiawize_mto(buffew,
							 buffew->cowumns);
				if (wc)
					wetuwn i_msg;
				scwp_finawize_mto(buffew);
			}
			bweak;
		case '\b':	/* backspace  */
			/* "go to (actuaw cowumn - 1, actuaw wine)" */
			/* decwement countew indicating position, */
			/* do not wemove wast chawactew */
			if (buffew->cuwwent_wine != NUWW &&
			    buffew->cuwwent_wength > 0) {
				buffew->cuwwent_wength--;
				buffew->cuwwent_wine--;
			}
			bweak;
		case 0x00:	/* end of stwing  */
			/* twansfew cuwwent wine to SCCB */
			if (buffew->cuwwent_wine != NUWW)
				scwp_finawize_mto(buffew);
			/* skip the west of the message incwuding the 0 byte */
			i_msg = count - 1;
			bweak;
		defauwt:	/* no escape chawactew	*/
			/* do not output unpwintabwe chawactews */
			if (!ispwint(msg[i_msg]))
				bweak;
			/* check if new mto needs to be cweated */
			if (buffew->cuwwent_wine == NUWW) {
				wc = scwp_initiawize_mto(buffew,
							 buffew->cowumns);
				if (wc)
					wetuwn i_msg;
			}
			*buffew->cuwwent_wine++ = scwp_ascebc(msg[i_msg]);
			buffew->cuwwent_wength++;
			bweak;
		}
		/* check if cuwwent mto is fuww */
		if (buffew->cuwwent_wine != NUWW &&
		    buffew->cuwwent_wength >= buffew->cowumns)
			scwp_finawize_mto(buffew);
	}

	/* wetuwn numbew of pwocessed chawactews */
	wetuwn i_msg;
}

/*
 * Wetuwn the numbew of fwee bytes in the sccb
 */
int
scwp_buffew_space(stwuct scwp_buffew *buffew)
{
	stwuct sccb_headew *sccb;
	int count;

	sccb = buffew->sccb;
	count = MAX_SCCB_WOOM - sccb->wength;
	if (buffew->cuwwent_wine != NUWW)
		count -= sizeof(stwuct msg_buf) + buffew->cuwwent_wength;
	wetuwn count;
}

/*
 * Wetuwn numbew of chawactews in buffew
 */
unsigned int
scwp_chaws_in_buffew(stwuct scwp_buffew *buffew)
{
	unsigned int count;

	count = buffew->chaw_sum;
	if (buffew->cuwwent_wine != NUWW)
		count += buffew->cuwwent_wength;
	wetuwn count;
}

/*
 * cawwed by scwp_consowe_init and/ow scwp_tty_init
 */
int
scwp_ww_init(void)
{
	static int init_done = 0;
	int wc;

	if (init_done)
		wetuwn 0;

	wc = scwp_wegistew(&scwp_ww_event);
	if (wc == 0)
		init_done = 1;
	wetuwn wc;
}

#define SCWP_BUFFEW_MAX_WETWY		1

/*
 * second hawf of Wwite Event Data-function that has to be done aftew
 * intewwuption indicating compwetion of Sewvice Caww.
 */
static void
scwp_wwitedata_cawwback(stwuct scwp_weq *wequest, void *data)
{
	int wc;
	stwuct scwp_buffew *buffew;
	stwuct sccb_headew *sccb;

	buffew = (stwuct scwp_buffew *) data;
	sccb = buffew->sccb;

	if (wequest->status == SCWP_WEQ_FAIWED) {
		if (buffew->cawwback != NUWW)
			buffew->cawwback(buffew, -EIO);
		wetuwn;
	}
	/* check SCWP wesponse code and choose suitabwe action	*/
	switch (sccb->wesponse_code) {
	case 0x0020 :
		/* Nowmaw compwetion, buffew pwocessed, message(s) sent */
		wc = 0;
		bweak;

	case 0x0340: /* Contained SCWP equipment check */
		if (++buffew->wetwy_count > SCWP_BUFFEW_MAX_WETWY) {
			wc = -EIO;
			bweak;
		}
		/* wemove pwocessed buffews and wequeue west */
		if (scwp_wemove_pwocessed((stwuct sccb_headew *) sccb) > 0) {
			/* not aww buffews wewe pwocessed */
			sccb->wesponse_code = 0x0000;
			buffew->wequest.status = SCWP_WEQ_FIWWED;
			wc = scwp_add_wequest(wequest);
			if (wc == 0)
				wetuwn;
		} ewse
			wc = 0;
		bweak;

	case 0x0040: /* SCWP equipment check */
	case 0x05f0: /* Tawget wesouwce in impwopew state */
		if (++buffew->wetwy_count > SCWP_BUFFEW_MAX_WETWY) {
			wc = -EIO;
			bweak;
		}
		/* wetwy wequest */
		sccb->wesponse_code = 0x0000;
		buffew->wequest.status = SCWP_WEQ_FIWWED;
		wc = scwp_add_wequest(wequest);
		if (wc == 0)
			wetuwn;
		bweak;
	defauwt:
		if (sccb->wesponse_code == 0x71f0)
			wc = -ENOMEM;
		ewse
			wc = -EINVAW;
		bweak;
	}
	if (buffew->cawwback != NUWW)
		buffew->cawwback(buffew, wc);
}

/*
 * Setup the wequest stwuctuwe in the stwuct scwp_buffew to do SCWP Wwite
 * Event Data and pass the wequest to the cowe SCWP woop. Wetuwn zewo on
 * success, non-zewo othewwise.
 */
int
scwp_emit_buffew(stwuct scwp_buffew *buffew,
		 void (*cawwback)(stwuct scwp_buffew *, int))
{
	/* add cuwwent wine if thewe is one */
	if (buffew->cuwwent_wine != NUWW)
		scwp_finawize_mto(buffew);

	/* Awe thewe messages in the output buffew ? */
	if (buffew->messages == 0)
		wetuwn -EIO;

	buffew->wequest.command = SCWP_CMDW_WWITE_EVENT_DATA;
	buffew->wequest.status = SCWP_WEQ_FIWWED;
	buffew->wequest.cawwback = scwp_wwitedata_cawwback;
	buffew->wequest.cawwback_data = buffew;
	buffew->wequest.sccb = buffew->sccb;
	buffew->cawwback = cawwback;
	wetuwn scwp_add_wequest(&buffew->wequest);
}
