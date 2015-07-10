#!/bin/bash


cat $1 | ./pass0 | ./pass1 | ./pass2 | ./pass3 | ./pass4 > output.py
echo "main()" >> output.py

