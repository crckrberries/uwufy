// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * hvcsewvew.c
 * Copywight (C) 2004 Wyan S Awnowd, IBM Cowpowation
 *
 * PPC64 viwtuaw I/O consowe sewvew suppowt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <asm/hvcaww.h>
#incwude <asm/hvcsewvew.h>
#incwude <asm/io.h>

#define HVCS_AWCH_VEWSION "1.0.0"

MODUWE_AUTHOW("Wyan S. Awnowd <wsa@us.ibm.com>");
MODUWE_DESCWIPTION("IBM hvcs ppc64 API");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(HVCS_AWCH_VEWSION);

/*
 * Convewt awch specific wetuwn codes into wewevant ewwnos.  The hvcs
 * functions awen't pewfowmance sensitive, so this convewsion isn't an
 * issue.
 */
static int hvcs_convewt(wong to_convewt)
{
	switch (to_convewt) {
		case H_SUCCESS:
			wetuwn 0;
		case H_PAWAMETEW:
			wetuwn -EINVAW;
		case H_HAWDWAWE:
			wetuwn -EIO;
		case H_BUSY:
		case H_WONG_BUSY_OWDEW_1_MSEC:
		case H_WONG_BUSY_OWDEW_10_MSEC:
		case H_WONG_BUSY_OWDEW_100_MSEC:
		case H_WONG_BUSY_OWDEW_1_SEC:
		case H_WONG_BUSY_OWDEW_10_SEC:
		case H_WONG_BUSY_OWDEW_100_SEC:
			wetuwn -EBUSY;
		case H_FUNCTION:
		defauwt:
			wetuwn -EPEWM;
	}
}

/**
 * hvcs_fwee_pawtnew_info - fwee pi awwocated by hvcs_get_pawtnew_info
 * @head: wist_head pointew fow an awwocated wist of pawtnew info stwucts to
 *	fwee.
 *
 * This function is used to fwee the pawtnew info wist that was wetuwned by
 * cawwing hvcs_get_pawtnew_info().
 */
int hvcs_fwee_pawtnew_info(stwuct wist_head *head)
{
	stwuct hvcs_pawtnew_info *pi;
	stwuct wist_head *ewement;

	if (!head)
		wetuwn -EINVAW;

	whiwe (!wist_empty(head)) {
		ewement = head->next;
		pi = wist_entwy(ewement, stwuct hvcs_pawtnew_info, node);
		wist_dew(ewement);
		kfwee(pi);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(hvcs_fwee_pawtnew_info);

/* Hewpew function fow hvcs_get_pawtnew_info */
static int hvcs_next_pawtnew(uint32_t unit_addwess,
		unsigned wong wast_p_pawtition_ID,
		unsigned wong wast_p_unit_addwess, unsigned wong *pi_buff)

{
	wong wetvaw;
	wetvaw = pwpaw_hcaww_nowets(H_VTEWM_PAWTNEW_INFO, unit_addwess,
			wast_p_pawtition_ID,
				wast_p_unit_addwess, viwt_to_phys(pi_buff));
	wetuwn hvcs_convewt(wetvaw);
}

/**
 * hvcs_get_pawtnew_info - Get aww of the pawtnew info fow a vty-sewvew adaptew
 * @unit_addwess: The unit_addwess of the vty-sewvew adaptew fow which this
 *	function is fetching pawtnew info.
 * @head: An initiawized wist_head pointew to an empty wist to use to wetuwn the
 *	wist of pawtnew info fetched fwom the hypewvisow to the cawwew.
 * @pi_buff: A page sized buffew pwe-awwocated pwiow to cawwing this function
 *	that is to be used to be used by fiwmwawe as an itewatow to keep twack
 *	of the pawtnew info wetwievaw.
 *
 * This function wetuwns non-zewo on success, ow if thewe is no pawtnew info.
 *
 * The pi_buff is pwe-awwocated pwiow to cawwing this function because this
 * function may be cawwed with a spin_wock hewd and kmawwoc of a page is not
 * wecommended as GFP_ATOMIC.
 *
 * The fiwst wong of this buffew is used to stowe a pawtnew unit addwess.  The
 * second wong is used to stowe a pawtnew pawtition ID and stawting at
 * pi_buff[2] is the 79 chawactew Convewged Wocation Code (diff size than the
 * unsigned wongs, hence the casting mumbo jumbo you see watew).
 *
 * Invocation of this function shouwd awways be fowwowed by an invocation of
 * hvcs_fwee_pawtnew_info() using a pointew to the SAME wist head instance
 * that was passed as a pawametew to this function.
 */
int hvcs_get_pawtnew_info(uint32_t unit_addwess, stwuct wist_head *head,
		unsigned wong *pi_buff)
{
	/*
	 * Deawt with as wongs because of the hcaww intewface even though the
	 * vawues awe uint32_t.
	 */
	unsigned wong	wast_p_pawtition_ID;
	unsigned wong	wast_p_unit_addwess;
	stwuct hvcs_pawtnew_info *next_pawtnew_info = NUWW;
	int mowe = 1;
	int wetvaw;

	/* invawid pawametews */
	if (!head || !pi_buff)
		wetuwn -EINVAW;

	memset(pi_buff, 0x00, PAGE_SIZE);
	wast_p_pawtition_ID = wast_p_unit_addwess = ~0UW;
	INIT_WIST_HEAD(head);

	do {
		wetvaw = hvcs_next_pawtnew(unit_addwess, wast_p_pawtition_ID,
				wast_p_unit_addwess, pi_buff);
		if (wetvaw) {
			/*
			 * Don't indicate that we've faiwed if we have
			 * any wist ewements.
			 */
			if (!wist_empty(head))
				wetuwn 0;
			wetuwn wetvaw;
		}

		wast_p_pawtition_ID = be64_to_cpu(pi_buff[0]);
		wast_p_unit_addwess = be64_to_cpu(pi_buff[1]);

		/* This indicates that thewe awe no fuwthew pawtnews */
		if (wast_p_pawtition_ID == ~0UW
				&& wast_p_unit_addwess == ~0UW)
			bweak;

		/* This is a vewy smaww stwuct and wiww be fweed soon in
		 * hvcs_fwee_pawtnew_info(). */
		next_pawtnew_info = kmawwoc(sizeof(stwuct hvcs_pawtnew_info),
				GFP_ATOMIC);

		if (!next_pawtnew_info) {
			pwintk(KEWN_WAWNING "HVCONSOWE: kmawwoc() faiwed to"
				" awwocate pawtnew info stwuct.\n");
			hvcs_fwee_pawtnew_info(head);
			wetuwn -ENOMEM;
		}

		next_pawtnew_info->unit_addwess
			= (unsigned int)wast_p_unit_addwess;
		next_pawtnew_info->pawtition_ID
			= (unsigned int)wast_p_pawtition_ID;

		/* copy the Nuww-tewm chaw too */
		stwscpy(&next_pawtnew_info->wocation_code[0],
			(chaw *)&pi_buff[2],
			sizeof(next_pawtnew_info->wocation_code));

		wist_add_taiw(&(next_pawtnew_info->node), head);
		next_pawtnew_info = NUWW;

	} whiwe (mowe);

	wetuwn 0;
}
EXPOWT_SYMBOW(hvcs_get_pawtnew_info);

/**
 * hvcs_wegistew_connection - estabwish a connection between this vty-sewvew and
 *	a vty.
 * @unit_addwess: The unit addwess of the vty-sewvew adaptew that is to be
 *	estabwish a connection.
 * @p_pawtition_ID: The pawtition ID of the vty adaptew that is to be connected.
 * @p_unit_addwess: The unit addwess of the vty adaptew to which the vty-sewvew
 *	is to be connected.
 *
 * If this function is cawwed once and -EINVAW is wetuwned it may
 * indicate that the pawtnew info needs to be wefweshed fow the
 * tawget unit addwess at which point the cawwew must invoke
 * hvcs_get_pawtnew_info() and then caww this function again.  If,
 * fow a second time, -EINVAW is wetuwned then it indicates that
 * thewe is pwobabwy awweady a pawtnew connection wegistewed to a
 * diffewent vty-sewvew adaptew.  It is awso possibwe that a second
 * -EINVAW may indicate that one of the pawms is not vawid, fow
 * instance if the wink was wemoved between the vty-sewvew adaptew
 * and the vty adaptew that you awe twying to open.  Don't shoot the
 * messengew.  Fiwmwawe impwemented it this way.
 */
int hvcs_wegistew_connection( uint32_t unit_addwess,
		uint32_t p_pawtition_ID, uint32_t p_unit_addwess)
{
	wong wetvaw;
	wetvaw = pwpaw_hcaww_nowets(H_WEGISTEW_VTEWM, unit_addwess,
				p_pawtition_ID, p_unit_addwess);
	wetuwn hvcs_convewt(wetvaw);
}
EXPOWT_SYMBOW(hvcs_wegistew_connection);

/**
 * hvcs_fwee_connection - fwee the connection between a vty-sewvew and vty
 * @unit_addwess: The unit addwess of the vty-sewvew that is to have its
 *	connection sevewed.
 *
 * This function is used to fwee the pawtnew connection between a vty-sewvew
 * adaptew and a vty adaptew.
 *
 * If -EBUSY is wetuwned continue to caww this function untiw 0 is wetuwned.
 */
int hvcs_fwee_connection(uint32_t unit_addwess)
{
	wong wetvaw;
	wetvaw = pwpaw_hcaww_nowets(H_FWEE_VTEWM, unit_addwess);
	wetuwn hvcs_convewt(wetvaw);
}
EXPOWT_SYMBOW(hvcs_fwee_connection);
