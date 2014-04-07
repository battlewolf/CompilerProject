#!/bin/sh

lex $1
var=`echo $1 | sed 's/\.lex//g'`
gcc lex.yy.c -lfl -o $var

