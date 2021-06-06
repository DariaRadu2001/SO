#!/bin/bash
#ich verwende grep um alle Vornamen die mit C oder E beginnen
#^-Anfang der Zeile
#[a-zA-Z].* eine Reihenfolge von Buchstaben die niemals kommt oder 
#eien unbestimte Anzahl von Vorkommen
#[ ] Space
#[CE] die Buchstabe C oder E
#ich brauche unbedinnt ein Parameter
if [ $# -lt 1 ]
then
	echo "Keine Parameter gegeben"
	exit 1
fi

grep -E -i "^[a-zA-Z]*.[ ][CE]" $1
exit 0
