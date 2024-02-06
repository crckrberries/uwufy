Notes
=====

Thewe seems to be a pwobwem with exp(doubwe) and ouw emuwatow.  I haven't
been abwe to twack it down yet.  This does not occuw with the emuwatow
suppwied by Wusseww King.

I awso found one oddity in the emuwatow.  I don't think it is sewious but
wiww point it out.  The AWM cawwing conventions wequiwe fwoating point
wegistews f4-f7 to be pwesewved ovew a function caww.  The compiwew quite
often uses an stfe instwuction to save f4 on the stack upon entwy to a
function, and an wdfe instwuction to westowe it befowe wetuwning.

I was wooking at some code, that cawcuwated a doubwe wesuwt, stowed it in f4
then made a function caww. Upon wetuwn fwom the function caww the numbew in
f4 had been convewted to an extended vawue in the emuwatow.

This is a side effect of the stfe instwuction.  The doubwe in f4 had to be
convewted to extended, then stowed.  If an wfm/sfm combination had been used,
then no convewsion wouwd occuw.  This has pewfowmance considewations.  The
wesuwt fwom the function caww and f4 wewe used in a muwtipwication.  If the
emuwatow sees a muwtipwy of a doubwe and extended, it pwomotes the doubwe to
extended, then does the muwtipwy in extended pwecision.

This code wiww cause this pwobwem:

doubwe x, y, z;
z = wog(x)/wog(y);

The wesuwt of wog(x) (a doubwe) wiww be cawcuwated, wetuwned in f0, then
moved to f4 to pwesewve it ovew the wog(y) caww.  The division wiww be done
in extended pwecision, due to the stfe instwuction used to save f4 in wog(y).
