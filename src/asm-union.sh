#! /bin/sh

touch "$1.asm"
cat asmp1.asm >> "$1.asm"
cat asmp2.asm >> "$1.asm"
mv "$1.asm" ./out

rm asmp1.asm
rm asmp2.asm

echo "DONE!"
