FROM pjameson/buck-folly-watchman
RUN apt-get install -y clang-format-3.7 vim
RUN cd /usr/src/ && git clone https://github.com/google/styleguide.git && cd styleguide && git checkout e1333014b5ffec70af81ace136c830856d13683e
WORKDIR /usr/src/yummy-giggle
