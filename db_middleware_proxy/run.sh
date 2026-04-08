#!/bin/bash
set -e

export PATH="/c/Program Files/PostgreSQL/9.4/bin:$PATH"

echo "== setup schema =="
psql test < schema.sql

echo "== build =="
gcc server.c -lpq -lpthread -o server

echo "== run =="
./server