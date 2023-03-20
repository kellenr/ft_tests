#!/bin/bash

auto_headers() {
  src_dir=$1
  H_FILE=auto_headers.h
  functions=$(for c_file in ${src_dir}/*/**/ft_*.c; do
    out=$(grep -oE "^\w+\s+\**ft_\w+\(.*\)" $c_file)
    read -r funcs <<<"$out"
    for fn in "$funcs"; do
      [ -n "$fn" ] && echo "$fn;"
    done
  done)

  cat >$H_FILE <<EOF
/* AUTO GENERATED FILE */
#ifndef TESTS_H
#define TESTS_H
${functions}
#endif
EOF
}

compile() {
  src_dir="${1}"
  PROGRAM_NAME=$2
  LDFLAGS="-lcheck -lsubunit -lm"
  MAIN_SRC="utils.c tests.c main.c"
  FT_SRC=$(ls ${src_dir}/*/ex*/ft_*.c)
  gcc -o $PROGRAM_NAME $MAIN_SRC $FT_SRC $LDFLAGS
}

run() {
  program=$1
  output=$(./$program)
  exit_code=${PIPESTATUS[0]}
  echo "${output}" |
    perl -pe 's/test: /test:\t/' |
    perl -pe 's/(test:.*)(\n)$/$1\t/' |
    perl -pe 's/failure/⚠️  failure/' |
    perl -pe 's/success/👍 success/' |
    sed -e 's/failure:.*$/\x1b[31m&\x1b[0m/' \
      -e 's/success:.*$/\x1b[32m&\x1b[0m/'
  if [ "${exit_code}" -ne 0 ]; then
    echo -e "\e[31mTESTS FAILED ⚠️ ⚠️ ⚠️\e[0m"
  else
    echo -e "\e[32mTESTS PASSED! 🎉🎉🎉\e[0m"
  fi
}

clean() {
  rm -f auto_*
}

main() {
  src_dir=$1
  auto_headers "${src_dir}"
  if compile "${src_dir}" "auto_test"; then
    run "auto_test"
  fi
  clean
}

if [[ ${BASH_SOURCE[0]} == "${0}" ]]; then
  main $@
fi
