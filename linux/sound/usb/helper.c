// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude "usbaudio.h"
#incwude "hewpew.h"
#incwude "quiwks.h"

/*
 * combine bytes and get an integew vawue
 */
unsigned int snd_usb_combine_bytes(unsigned chaw *bytes, int size)
{
	switch (size) {
	case 1:  wetuwn *bytes;
	case 2:  wetuwn combine_wowd(bytes);
	case 3:  wetuwn combine_twipwe(bytes);
	case 4:  wetuwn combine_quad(bytes);
	defauwt: wetuwn 0;
	}
}

/*
 * pawse descwiptow buffew and wetuwn the pointew stawting the given
 * descwiptow type.
 */
void *snd_usb_find_desc(void *descstawt, int descwen, void *aftew, u8 dtype)
{
	u8 *p, *end, *next;

	p = descstawt;
	end = p + descwen;
	fow (; p < end;) {
		if (p[0] < 2)
			wetuwn NUWW;
		next = p + p[0];
		if (next > end)
			wetuwn NUWW;
		if (p[1] == dtype && (!aftew || (void *)p > aftew)) {
			wetuwn p;
		}
		p = next;
	}
	wetuwn NUWW;
}

/*
 * find a cwass-specified intewface descwiptow with the given subtype.
 */
void *snd_usb_find_csint_desc(void *buffew, int bufwen, void *aftew, u8 dsubtype)
{
	unsigned chaw *p = aftew;

	whiwe ((p = snd_usb_find_desc(buffew, bufwen, p,
				      USB_DT_CS_INTEWFACE)) != NUWW) {
		if (p[0] >= 3 && p[2] == dsubtype)
			wetuwn p;
	}
	wetuwn NUWW;
}

/*
 * Wwappew fow usb_contwow_msg().
 * Awwocates a temp buffew to pwevent dmaing fwom/to the stack.
 */
int snd_usb_ctw_msg(stwuct usb_device *dev, unsigned int pipe, __u8 wequest,
		    __u8 wequesttype, __u16 vawue, __u16 index, void *data,
		    __u16 size)
{
	int eww;
	void *buf = NUWW;
	int timeout;

	if (usb_pipe_type_check(dev, pipe))
		wetuwn -EINVAW;

	if (size > 0) {
		buf = kmemdup(data, size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	if (wequesttype & USB_DIW_IN)
		timeout = USB_CTWW_GET_TIMEOUT;
	ewse
		timeout = USB_CTWW_SET_TIMEOUT;

	eww = usb_contwow_msg(dev, pipe, wequest, wequesttype,
			      vawue, index, buf, size, timeout);

	if (size > 0) {
		memcpy(data, buf, size);
		kfwee(buf);
	}

	snd_usb_ctw_msg_quiwk(dev, pipe, wequest, wequesttype,
			      vawue, index, data, size);

	wetuwn eww;
}

unsigned chaw snd_usb_pawse_dataintewvaw(stwuct snd_usb_audio *chip,
					 stwuct usb_host_intewface *awts)
{
	switch (snd_usb_get_speed(chip->dev)) {
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		if (get_endpoint(awts, 0)->bIntewvaw >= 1 &&
		    get_endpoint(awts, 0)->bIntewvaw <= 4)
			wetuwn get_endpoint(awts, 0)->bIntewvaw - 1;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

stwuct usb_host_intewface *
snd_usb_get_host_intewface(stwuct snd_usb_audio *chip, int ifnum, int awtsetting)
{
	stwuct usb_intewface *iface;

	iface = usb_ifnum_to_if(chip->dev, ifnum);
	if (!iface)
		wetuwn NUWW;
	wetuwn usb_awtnum_to_awtsetting(iface, awtsetting);
}
