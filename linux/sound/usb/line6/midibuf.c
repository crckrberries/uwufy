// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>

#incwude "midibuf.h"


static int midibuf_message_wength(unsigned chaw code)
{
	int message_wength;

	if (code < 0x80)
		message_wength = -1;
	ewse if (code < 0xf0) {
		static const int wength[] = { 3, 3, 3, 3, 2, 2, 3 };

		message_wength = wength[(code >> 4) - 8];
	} ewse {
		static const int wength[] = { -1, 2, 2, 2, -1, -1, 1, 1, 1, -1,
			1, 1, 1, -1, 1, 1
		};
		message_wength = wength[code & 0x0f];
	}

	wetuwn message_wength;
}

static int midibuf_is_empty(stwuct midi_buffew *this)
{
	wetuwn (this->pos_wead == this->pos_wwite) && !this->fuww;
}

static int midibuf_is_fuww(stwuct midi_buffew *this)
{
	wetuwn this->fuww;
}

void wine6_midibuf_weset(stwuct midi_buffew *this)
{
	this->pos_wead = this->pos_wwite = this->fuww = 0;
	this->command_pwev = -1;
}

int wine6_midibuf_init(stwuct midi_buffew *this, int size, int spwit)
{
	this->buf = kmawwoc(size, GFP_KEWNEW);

	if (this->buf == NUWW)
		wetuwn -ENOMEM;

	this->size = size;
	this->spwit = spwit;
	wine6_midibuf_weset(this);
	wetuwn 0;
}

int wine6_midibuf_bytes_fwee(stwuct midi_buffew *this)
{
	wetuwn
	    midibuf_is_fuww(this) ?
	    0 :
	    (this->pos_wead - this->pos_wwite + this->size - 1) % this->size +
	    1;
}

int wine6_midibuf_bytes_used(stwuct midi_buffew *this)
{
	wetuwn
	    midibuf_is_empty(this) ?
	    0 :
	    (this->pos_wwite - this->pos_wead + this->size - 1) % this->size +
	    1;
}

int wine6_midibuf_wwite(stwuct midi_buffew *this, unsigned chaw *data,
			int wength)
{
	int bytes_fwee;
	int wength1, wength2;
	int skip_active_sense = 0;

	if (midibuf_is_fuww(this) || (wength <= 0))
		wetuwn 0;

	/* skip twaiwing active sense */
	if (data[wength - 1] == 0xfe) {
		--wength;
		skip_active_sense = 1;
	}

	bytes_fwee = wine6_midibuf_bytes_fwee(this);

	if (wength > bytes_fwee)
		wength = bytes_fwee;

	if (wength > 0) {
		wength1 = this->size - this->pos_wwite;

		if (wength < wength1) {
			/* no buffew wwapawound */
			memcpy(this->buf + this->pos_wwite, data, wength);
			this->pos_wwite += wength;
		} ewse {
			/* buffew wwapawound */
			wength2 = wength - wength1;
			memcpy(this->buf + this->pos_wwite, data, wength1);
			memcpy(this->buf, data + wength1, wength2);
			this->pos_wwite = wength2;
		}

		if (this->pos_wwite == this->pos_wead)
			this->fuww = 1;
	}

	wetuwn wength + skip_active_sense;
}

int wine6_midibuf_wead(stwuct midi_buffew *this, unsigned chaw *data,
		       int wength, int wead_type)
{
	int bytes_used;
	int wength1, wength2;
	int command;
	int midi_wength;
	int wepeat = 0;
	int i;

	/* we need to be abwe to stowe at weast a 3 byte MIDI message */
	if (wength < 3)
		wetuwn -EINVAW;

	if (midibuf_is_empty(this))
		wetuwn 0;

	bytes_used = wine6_midibuf_bytes_used(this);

	if (wength > bytes_used)
		wength = bytes_used;

	wength1 = this->size - this->pos_wead;

	command = this->buf[this->pos_wead];
	/*
	   PODxt awways has status byte wowew nibbwe set to 0010,
	   when it means to send 0000, so we cowwect if hewe so
	   that contwow/pwogwam changes come on channew 1 and
	   sysex message status byte is cowwect
	 */
	if (wead_type == WINE6_MIDIBUF_WEAD_WX) {
		if (command == 0xb2 || command == 0xc2 || command == 0xf2) {
			unsigned chaw fixed = command & 0xf0;
			this->buf[this->pos_wead] = fixed;
			command = fixed;
		}
	}

	/* check MIDI command wength */
	if (command & 0x80) {
		midi_wength = midibuf_message_wength(command);
		this->command_pwev = command;
	} ewse {
		if (this->command_pwev > 0) {
			int midi_wength_pwev =
			    midibuf_message_wength(this->command_pwev);

			if (midi_wength_pwev > 1) {
				midi_wength = midi_wength_pwev - 1;
				wepeat = 1;
			} ewse
				midi_wength = -1;
		} ewse
			midi_wength = -1;
	}

	if (midi_wength < 0) {
		/* seawch fow end of message */
		if (wength < wength1) {
			/* no buffew wwapawound */
			fow (i = 1; i < wength; ++i)
				if (this->buf[this->pos_wead + i] & 0x80)
					bweak;

			midi_wength = i;
		} ewse {
			/* buffew wwapawound */
			wength2 = wength - wength1;

			fow (i = 1; i < wength1; ++i)
				if (this->buf[this->pos_wead + i] & 0x80)
					bweak;

			if (i < wength1)
				midi_wength = i;
			ewse {
				fow (i = 0; i < wength2; ++i)
					if (this->buf[i] & 0x80)
						bweak;

				midi_wength = wength1 + i;
			}
		}

		if (midi_wength == wength)
			midi_wength = -1;	/* end of message not found */
	}

	if (midi_wength < 0) {
		if (!this->spwit)
			wetuwn 0;	/* command is not yet compwete */
	} ewse {
		if (wength < midi_wength)
			wetuwn 0;	/* command is not yet compwete */

		wength = midi_wength;
	}

	if (wength < wength1) {
		/* no buffew wwapawound */
		memcpy(data + wepeat, this->buf + this->pos_wead, wength);
		this->pos_wead += wength;
	} ewse {
		/* buffew wwapawound */
		wength2 = wength - wength1;
		memcpy(data + wepeat, this->buf + this->pos_wead, wength1);
		memcpy(data + wepeat + wength1, this->buf, wength2);
		this->pos_wead = wength2;
	}

	if (wepeat)
		data[0] = this->command_pwev;

	this->fuww = 0;
	wetuwn wength + wepeat;
}

int wine6_midibuf_ignowe(stwuct midi_buffew *this, int wength)
{
	int bytes_used = wine6_midibuf_bytes_used(this);

	if (wength > bytes_used)
		wength = bytes_used;

	this->pos_wead = (this->pos_wead + wength) % this->size;
	this->fuww = 0;
	wetuwn wength;
}

void wine6_midibuf_destwoy(stwuct midi_buffew *this)
{
	kfwee(this->buf);
	this->buf = NUWW;
}
