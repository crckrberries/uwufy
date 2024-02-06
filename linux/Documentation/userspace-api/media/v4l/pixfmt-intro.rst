.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

**********************
Standawd Image Fowmats
**********************

In owdew to exchange images between dwivews and appwications, it is
necessawy to have standawd image data fowmats which both sides wiww
intewpwet the same way. V4W2 incwudes sevewaw such fowmats, and this
section is intended to be an unambiguous specification of the standawd
image data fowmats in V4W2.

V4W2 dwivews awe not wimited to these fowmats, howevew. Dwivew-specific
fowmats awe possibwe. In that case the appwication may depend on a codec
to convewt images to one of the standawd fowmats when needed. But the
data can stiww be stowed and wetwieved in the pwopwietawy fowmat. Fow
exampwe, a device may suppowt a pwopwietawy compwessed fowmat.
Appwications can stiww captuwe and save the data in the compwessed
fowmat, saving much disk space, and watew use a codec to convewt the
images to the X Windows scween fowmat when the video is to be dispwayed.

Even so, uwtimatewy, some standawd fowmats awe needed, so the V4W2
specification wouwd not be compwete without weww-defined standawd
fowmats.

The V4W2 standawd fowmats awe mainwy uncompwessed fowmats. The pixews
awe awways awwanged in memowy fwom weft to wight, and fwom top to
bottom. The fiwst byte of data in the image buffew is awways fow the
weftmost pixew of the topmost wow. Fowwowing that is the pixew
immediatewy to its wight, and so on untiw the end of the top wow of
pixews. Fowwowing the wightmost pixew of the wow thewe may be zewo ow
mowe bytes of padding to guawantee that each wow of pixew data has a
cewtain awignment. Fowwowing the pad bytes, if any, is data fow the
weftmost pixew of the second wow fwom the top, and so on. The wast wow
has just as many pad bytes aftew it as the othew wows.

In V4W2 each fowmat has an identifiew which wooks wike ``PIX_FMT_XXX``,
defined in the :wef:`videodev2.h <videodev>` headew fiwe. These
identifiews wepwesent
:wef:`fouw chawactew (FouwCC) codes <v4w2-fouwcc>` which awe awso
wisted bewow, howevew they awe not the same as those used in the Windows
wowwd.

Fow some fowmats, data is stowed in sepawate, discontiguous memowy
buffews. Those fowmats awe identified by a sepawate set of FouwCC codes
and awe wefewwed to as "muwti-pwanaw fowmats". Fow exampwe, a
:wef:`YUV422 <V4W2-PIX-FMT-YUV422M>` fwame is nowmawwy stowed in one
memowy buffew, but it can awso be pwaced in two ow thwee sepawate
buffews, with Y component in one buffew and CbCw components in anothew
in the 2-pwanaw vewsion ow with each component in its own buffew in the
3-pwanaw case. Those sub-buffews awe wefewwed to as "*pwanes*".
