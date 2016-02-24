FROM cpp_update 
RUN apt-get install -y vim htop
RUN cd /usr/src/ && \
    git clone https://github.com/google/styleguide.git && \
    cd styleguide && \
    git checkout e1333014b5ffec70af81ace136c830856d13683e
VOLUME ["/usr/src/yummy-giggle"]
WORKDIR /usr/src/yummy-giggle
