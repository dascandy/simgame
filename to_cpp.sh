#!/bin/bash

echo "unsigned char "`echo $1 | sed -e 's/\./_/g'`"[] = {";
cat $1 | hexdump -v -e '/1 "0x%02x, "'
echo "0x00 };";
