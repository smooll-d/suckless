#!/bin/bash

disksize=$(duf -only local -output size,used,avail | awk 'FNR==6{ print $4"/"$2 " " "("$6")" }')

echo ^b#e55887^^c#000000^" 󰋊 "^d^^c#e55887^ $disksize ^d^
