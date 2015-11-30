FROM pjameson/buck-folly-watchman
RUN apt-get install -y clang-format-3.7 vim
WORKDIR /usr/src/yummy-giggle
