#!/usr/bin/env bash

cd "$(dirname "${BASH_SOURCE[0]}")"
cd ../build/dev_x86_64

REPO="licaili193/remote_control"

# Fail on first error.
set -e
docker build -t $REPO .
echo "Built new image"
