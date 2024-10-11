FROM gcc:12.3.0

WORKDIR /app

RUN apt-get update && apt-get install -y \
    cmake \
    wget \
    && rm -rf /var/lib/apt/lists/*
    
RUN wget https://sourceforge.net/projects/boost/files/boost/1.74.0/boost_1_74_0.tar.gz/download -O boost_1_74_0.tar.gz

RUN tar -xvf boost_1_74_0.tar.gz
WORKDIR /app/boost_1_74_0
RUN ./bootstrap.sh
RUN ./b2 install

COPY ./app/ /app
WORKDIR /app/build
RUN cmake ..
RUN make

RUN chmod +x /app/start.sh

CMD ["/app/start.sh"]