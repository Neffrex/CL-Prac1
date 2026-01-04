#!/usr/bin/env bash

set -euo pipefail

REQ_FILE="requirements"

# Check for root privileges
if [[ "$EUID" -ne 0 ]]; then
  echo "This script must be run as root."
  echo "Please rerun it with:"
	echo "  sudo $0 $*"
  exit 1
fi

# Check requirements file
if [[ ! -f "$REQ_FILE" ]]; then
  echo "Requirements file not found: $REQ_FILE"
  exit 1
fi

echo "Updating package list..."
apt-get update

echo
echo "Installing packages..."
apt-get install -y $(tr ' ' '\n' < "$REQ_FILE")

echo "Done."
