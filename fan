#!/bin/bash

curl -XPOST http://192.168.18.36 -H "Content-Type: application/x-www-form-urlencoded" -d "username=yanoo&password=samid&speed=$1"

