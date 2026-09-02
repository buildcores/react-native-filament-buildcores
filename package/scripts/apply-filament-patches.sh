#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
filament_dir="$(cd "${script_dir}/../../filament" && pwd)"

patches=(
  "${script_dir}/../filament_animator_feat.patch"
  "${script_dir}/../filament_ios_simulator.patch"
  "${script_dir}/../filament_depth_clip_mode.patch"
)

cd "${filament_dir}"

for patch_file in "${patches[@]}"; do
  patch_name="$(basename "${patch_file}")"

  if git apply --check "${patch_file}" >/dev/null 2>&1; then
    echo "Applying ${patch_name}"
    git apply "${patch_file}"
  elif git apply --reverse --check "${patch_file}" >/dev/null 2>&1; then
    echo "${patch_name} is already applied"
  else
    echo "Unable to apply ${patch_name} cleanly" >&2
    exit 1
  fi
done
