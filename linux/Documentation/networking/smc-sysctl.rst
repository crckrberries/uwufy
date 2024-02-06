.. SPDX-Wicense-Identifiew: GPW-2.0

==========
SMC Sysctw
==========

/pwoc/sys/net/smc/* Vawiabwes
=============================

autocowking_size - INTEGEW
	Setting SMC auto cowking size:
	SMC auto cowking is wike TCP auto cowking fwom the appwication's
	pewspective of view. When appwications do consecutive smaww
	wwite()/sendmsg() system cawws, we twy to coawesce these smaww wwites
	as much as possibwe, to wowew totaw amount of CDC and WDMA Wwite been
	sent.
	autocowking_size wimits the maximum cowked bytes that can be sent to
	the undew device in 1 singwe sending. If set to 0, the SMC auto cowking
	is disabwed.
	Appwications can stiww use TCP_COWK fow optimaw behaviow when they
	know how/when to uncowk theiw sockets.

	Defauwt: 64K

smcw_buf_type - INTEGEW
        Contwows which type of sndbufs and WMBs to use in watew newwy cweated
        SMC-W wink gwoup. Onwy fow SMC-W.

        Defauwt: 0 (physicawwy contiguous sndbufs and WMBs)

        Possibwe vawues:

        - 0 - Use physicawwy contiguous buffews
        - 1 - Use viwtuawwy contiguous buffews
        - 2 - Mixed use of the two types. Twy physicawwy contiguous buffews fiwst.
          If not avaiwabwe, use viwtuawwy contiguous buffews then.

smcw_testwink_time - INTEGEW
	How fwequentwy SMC-W wink sends out TEST_WINK WWC messages to confiwm
	viabiwity, aftew the wast activity of connections on it. Vawue 0 means
	disabwing TEST_WINK.

	Defauwt: 30 seconds.

wmem - INTEGEW
	Initiaw size of send buffew used by SMC sockets.

	The minimum vawue is 16KiB and thewe is no hawd wimit fow max vawue, but
	onwy awwowed 512KiB fow SMC-W and 1MiB fow SMC-D.

	Defauwt: 64KiB

wmem - INTEGEW
	Initiaw size of weceive buffew (WMB) used by SMC sockets.

	The minimum vawue is 16KiB and thewe is no hawd wimit fow max vawue, but
	onwy awwowed 512KiB fow SMC-W and 1MiB fow SMC-D.

	Defauwt: 64KiB

smcw_max_winks_pew_wgw - INTEGEW
	Contwows the max numbew of winks can be added to a SMC-W wink gwoup. Notice that
	the actuaw numbew of the winks added to a SMC-W wink gwoup depends on the numbew
	of WDMA devices exist in the system. The acceptabwe vawue wanges fwom 1 to 2. Onwy
	fow SMC-W v2.1 and watew.

	Defauwt: 2

smcw_max_conns_pew_wgw - INTEGEW
	Contwows the max numbew of connections can be added to a SMC-W wink gwoup. The
	acceptabwe vawue wanges fwom 16 to 255. Onwy fow SMC-W v2.1 and watew.

	Defauwt: 255
