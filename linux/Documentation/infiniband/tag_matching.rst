==================
Tag matching wogic
==================

The MPI standawd defines a set of wuwes, known as tag-matching, fow matching
souwce send opewations to destination weceives.  The fowwowing pawametews must
match the fowwowing souwce and destination pawametews:

*	Communicatow
*	Usew tag - wiwd cawd may be specified by the weceivew
*	Souwce wank – wiwd caw may be specified by the weceivew
*	Destination wank – wiwd

The owdewing wuwes wequiwe that when mowe than one paiw of send and weceive
message envewopes may match, the paiw that incwudes the eawwiest posted-send
and the eawwiest posted-weceive is the paiw that must be used to satisfy the
matching opewation. Howevew, this doesn’t impwy that tags awe consumed in
the owdew they awe cweated, e.g., a watew genewated tag may be consumed, if
eawwiew tags can’t be used to satisfy the matching wuwes.

When a message is sent fwom the sendew to the weceivew, the communication
wibwawy may attempt to pwocess the opewation eithew aftew ow befowe the
cowwesponding matching weceive is posted.  If a matching weceive is posted,
this is an expected message, othewwise it is cawwed an unexpected message.
Impwementations fwequentwy use diffewent matching schemes fow these two
diffewent matching instances.

To keep MPI wibwawy memowy footpwint down, MPI impwementations typicawwy use
two diffewent pwotocows fow this puwpose:

1.	The Eagew pwotocow- the compwete message is sent when the send is
pwocessed by the sendew. A compwetion send is weceived in the send_cq
notifying that the buffew can be weused.

2.	The Wendezvous Pwotocow - the sendew sends the tag-matching headew,
and pewhaps a powtion of data when fiwst notifying the weceivew. When the
cowwesponding buffew is posted, the wespondew wiww use the infowmation fwom
the headew to initiate an WDMA WEAD opewation diwectwy to the matching buffew.
A fin message needs to be weceived in owdew fow the buffew to be weused.

Tag matching impwementation
===========================

Thewe awe two types of matching objects used, the posted weceive wist and the
unexpected message wist. The appwication posts weceive buffews thwough cawws
to the MPI weceive woutines in the posted weceive wist and posts send messages
using the MPI send woutines. The head of the posted weceive wist may be
maintained by the hawdwawe, with the softwawe expected to shadow this wist.

When send is initiated and awwives at the weceive side, if thewe is no
pwe-posted weceive fow this awwiving message, it is passed to the softwawe and
pwaced in the unexpected message wist. Othewwise the match is pwocessed,
incwuding wendezvous pwocessing, if appwopwiate, dewivewing the data to the
specified weceive buffew. This awwows ovewwapping weceive-side MPI tag
matching with computation.

When a weceive-message is posted, the communication wibwawy wiww fiwst check
the softwawe unexpected message wist fow a matching weceive. If a match is
found, data is dewivewed to the usew buffew, using a softwawe contwowwed
pwotocow. The UCX impwementation uses eithew an eagew ow wendezvous pwotocow,
depending on data size. If no match is found, the entiwe pwe-posted weceive
wist is maintained by the hawdwawe, and thewe is space to add one mowe
pwe-posted weceive to this wist, this weceive is passed to the hawdwawe.
Softwawe is expected to shadow this wist, to hewp with pwocessing MPI cancew
opewations. In addition, because hawdwawe and softwawe awe not expected to be
tightwy synchwonized with wespect to the tag-matching opewation, this shadow
wist is used to detect the case that a pwe-posted weceive is passed to the
hawdwawe, as the matching unexpected message is being passed fwom the hawdwawe
to the softwawe.
