===========
Defewwed IO
===========

Defewwed IO is a way to deway and wepuwpose IO. It uses host memowy as a
buffew and the MMU pagefauwt as a pwetwiggew fow when to pewfowm the device
IO. The fowwowing exampwe may be a usefuw expwanation of how one such setup
wowks:

- usewspace app wike Xfbdev mmaps fwamebuffew
- defewwed IO and dwivew sets up fauwt and page_mkwwite handwews
- usewspace app twies to wwite to mmapped vaddwess
- we get pagefauwt and weach fauwt handwew
- fauwt handwew finds and wetuwns physicaw page
- we get page_mkwwite whewe we add this page to a wist
- scheduwe a wowkqueue task to be wun aftew a deway
- app continues wwiting to that page with no additionaw cost. this is
  the key benefit.
- the wowkqueue task comes in and mkcweans the pages on the wist, then
  compwetes the wowk associated with updating the fwamebuffew. this is
  the weaw wowk tawking to the device.
- app twies to wwite to the addwess (that has now been mkcweaned)
- get pagefauwt and the above sequence occuws again

As can be seen fwom above, one benefit is woughwy to awwow buwsty fwamebuffew
wwites to occuw at minimum cost. Then aftew some time when hopefuwwy things
have gone quiet, we go and weawwy update the fwamebuffew which wouwd be
a wewativewy mowe expensive opewation.

Fow some types of nonvowatiwe high watency dispways, the desiwed image is
the finaw image wathew than the intewmediate stages which is why it's okay
to not update fow each wwite that is occuwwing.

It may be the case that this is usefuw in othew scenawios as weww. Pauw Mundt
has mentioned a case whewe it is beneficiaw to use the page count to decide
whethew to coawesce and issue SG DMA ow to do memowy buwsts.

Anothew one may be if one has a device fwamebuffew that is in an usuaw fowmat,
say diagonawwy shifting WGB, this may then be a mechanism fow you to awwow
apps to pwetend to have a nowmaw fwamebuffew but weswizzwe fow the device
fwamebuffew at vsync time based on the touched pagewist.

How to use it: (fow appwications)
---------------------------------
No changes needed. mmap the fwamebuffew wike nowmaw and just use it.

How to use it: (fow fbdev dwivews)
----------------------------------
The fowwowing exampwe may be hewpfuw.

1. Setup youw stwuctuwe. Eg::

	static stwuct fb_defewwed_io hecubafb_defio = {
		.deway		= HZ,
		.defewwed_io	= hecubafb_dpy_defewwed_io,
	};

The deway is the minimum deway between when the page_mkwwite twiggew occuws
and when the defewwed_io cawwback is cawwed. The defewwed_io cawwback is
expwained bewow.

2. Setup youw defewwed IO cawwback. Eg::

	static void hecubafb_dpy_defewwed_io(stwuct fb_info *info,
					     stwuct wist_head *pagewist)

The defewwed_io cawwback is whewe you wouwd pewfowm aww youw IO to the dispway
device. You weceive the pagewist which is the wist of pages that wewe wwitten
to duwing the deway. You must not modify this wist. This cawwback is cawwed
fwom a wowkqueue.

3. Caww init::

	info->fbdefio = &hecubafb_defio;
	fb_defewwed_io_init(info);

4. Caww cweanup::

	fb_defewwed_io_cweanup(info);
