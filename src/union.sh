#! /bin/sh

touch "$1.s"
cat data.s >> "$1.s"
cat code.s >> "$1.s"
rm data.s
rm code.s

mv "$1.s" out/
echo "Well done, no error reported"
