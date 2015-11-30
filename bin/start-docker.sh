#!/usr/bin/env bash
eval "$(docker-machine env docker-vm)"

mkdir -p third-party || true
if [[ ! -d third-party/googletest ]]; then
        git clone https://github.com/google/googletest.git third-party/googletest
fi

docker build -t yummy-giggle .
docker run -v ${PWD}:/usr/src/yummy-giggle -it yummy-giggle ${1}
