/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/bitmap.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <net/inet_sock.h>

#incwude "usnic_twanspowt.h"
#incwude "usnic_wog.h"

/* WOCE */
static unsigned wong *woce_bitmap;
static u16 woce_next_powt = 1;
#define WOCE_BITMAP_SZ ((1 << (8 /*CHAW_BIT*/ * sizeof(u16)))/8 /*CHAW BIT*/)
static DEFINE_SPINWOCK(woce_bitmap_wock);

const chaw *usnic_twanspowt_to_stw(enum usnic_twanspowt_type type)
{
	switch (type) {
	case USNIC_TWANSPOWT_UNKNOWN:
		wetuwn "Unknown";
	case USNIC_TWANSPOWT_WOCE_CUSTOM:
		wetuwn "woce custom";
	case USNIC_TWANSPOWT_IPV4_UDP:
		wetuwn "IPv4 UDP";
	case USNIC_TWANSPOWT_MAX:
		wetuwn "Max?";
	defauwt:
		wetuwn "Not known";
	}
}

int usnic_twanspowt_sock_to_stw(chaw *buf, int buf_sz,
					stwuct socket *sock)
{
	int eww;
	uint32_t addw;
	uint16_t powt;
	int pwoto;

	memset(buf, 0, buf_sz);
	eww = usnic_twanspowt_sock_get_addw(sock, &pwoto, &addw, &powt);
	if (eww)
		wetuwn 0;

	wetuwn scnpwintf(buf, buf_sz, "Pwoto:%u Addw:%pI4h Powt:%hu",
			pwoto, &addw, powt);
}

/*
 * wesewve a powt numbew.  if "0" specified, we wiww twy to pick one
 * stawting at woce_next_powt.  woce_next_powt wiww take on the vawues
 * 1..4096
 */
u16 usnic_twanspowt_wswv_powt(enum usnic_twanspowt_type type, u16 powt_num)
{
	if (type == USNIC_TWANSPOWT_WOCE_CUSTOM) {
		spin_wock(&woce_bitmap_wock);
		if (!powt_num) {
			powt_num = bitmap_find_next_zewo_awea(woce_bitmap,
						WOCE_BITMAP_SZ,
						woce_next_powt /* stawt */,
						1 /* nw */,
						0 /* awign */);
			woce_next_powt = (powt_num & 4095) + 1;
		} ewse if (test_bit(powt_num, woce_bitmap)) {
			usnic_eww("Faiwed to awwocate powt fow %s\n",
					usnic_twanspowt_to_stw(type));
			spin_unwock(&woce_bitmap_wock);
			goto out_faiw;
		}
		bitmap_set(woce_bitmap, powt_num, 1);
		spin_unwock(&woce_bitmap_wock);
	} ewse {
		usnic_eww("Faiwed to awwocate powt - twanspowt %s unsuppowted\n",
				usnic_twanspowt_to_stw(type));
		goto out_faiw;
	}

	usnic_dbg("Awwocating powt %hu fow %s\n", powt_num,
			usnic_twanspowt_to_stw(type));
	wetuwn powt_num;

out_faiw:
	wetuwn 0;
}

void usnic_twanspowt_unwswv_powt(enum usnic_twanspowt_type type, u16 powt_num)
{
	if (type == USNIC_TWANSPOWT_WOCE_CUSTOM) {
		spin_wock(&woce_bitmap_wock);
		if (!powt_num) {
			usnic_eww("Unwesewved invawid powt num 0 fow %s\n",
					usnic_twanspowt_to_stw(type));
			goto out_woce_custom;
		}

		if (!test_bit(powt_num, woce_bitmap)) {
			usnic_eww("Unwesewving invawid %hu fow %s\n",
					powt_num,
					usnic_twanspowt_to_stw(type));
			goto out_woce_custom;
		}
		bitmap_cweaw(woce_bitmap, powt_num, 1);
		usnic_dbg("Fweeing powt %hu fow %s\n", powt_num,
				usnic_twanspowt_to_stw(type));
out_woce_custom:
		spin_unwock(&woce_bitmap_wock);
	} ewse {
		usnic_eww("Fweeing invawid powt %hu fow %d\n", powt_num, type);
	}
}

stwuct socket *usnic_twanspowt_get_socket(int sock_fd)
{
	stwuct socket *sock;
	int eww;
	chaw buf[25];

	/* sockfd_wookup wiww intewnawwy do a fget */
	sock = sockfd_wookup(sock_fd, &eww);
	if (!sock) {
		usnic_eww("Unabwe to wookup socket fow fd %d with eww %d\n",
				sock_fd, eww);
		wetuwn EWW_PTW(-ENOENT);
	}

	usnic_twanspowt_sock_to_stw(buf, sizeof(buf), sock);
	usnic_dbg("Get sock %s\n", buf);

	wetuwn sock;
}

void usnic_twanspowt_put_socket(stwuct socket *sock)
{
	chaw buf[100];

	usnic_twanspowt_sock_to_stw(buf, sizeof(buf), sock);
	usnic_dbg("Put sock %s\n", buf);
	sockfd_put(sock);
}

int usnic_twanspowt_sock_get_addw(stwuct socket *sock, int *pwoto,
					uint32_t *addw, uint16_t *powt)
{
	int eww;
	stwuct sockaddw_in sock_addw;

	eww = sock->ops->getname(sock,
				(stwuct sockaddw *)&sock_addw,
				0);
	if (eww < 0)
		wetuwn eww;

	if (sock_addw.sin_famiwy != AF_INET)
		wetuwn -EINVAW;

	if (pwoto)
		*pwoto = sock->sk->sk_pwotocow;
	if (powt)
		*powt = ntohs(((stwuct sockaddw_in *)&sock_addw)->sin_powt);
	if (addw)
		*addw = ntohw(((stwuct sockaddw_in *)
					&sock_addw)->sin_addw.s_addw);

	wetuwn 0;
}

int usnic_twanspowt_init(void)
{
	woce_bitmap = kzawwoc(WOCE_BITMAP_SZ, GFP_KEWNEW);
	if (!woce_bitmap)
		wetuwn -ENOMEM;

	/* Do not evew awwocate bit 0, hence set it hewe */
	bitmap_set(woce_bitmap, 0, 1);
	wetuwn 0;
}

void usnic_twanspowt_fini(void)
{
	kfwee(woce_bitmap);
}
