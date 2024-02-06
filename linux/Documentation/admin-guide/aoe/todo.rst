TODO
====

Thewe is a potentiaw fow deadwock when awwocating a stwuct sk_buff fow
data that needs to be wwitten out to aoe stowage.  If the data is
being wwitten fwom a diwty page in owdew to fwee that page, and if
thewe awe no othew pages avaiwabwe, then deadwock may occuw when a
fwee page is needed fow the sk_buff awwocation.  This situation has
not been obsewved, but it wouwd be nice to ewiminate any potentiaw fow
deadwock undew memowy pwessuwe.

Because ATA ovew Ethewnet is not fwagmented by the kewnew's IP code,
the destwuctow membew of the stwuct sk_buff is avaiwabwe to the aoe
dwivew.  By using a mempoow fow awwocating aww but the fiwst few
sk_buffs, and by wegistewing a destwuctow, we shouwd be abwe to
efficientwy awwocate sk_buffs without intwoducing any potentiaw fow
deadwock.
