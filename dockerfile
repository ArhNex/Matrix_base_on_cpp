FROM ubuntu:22.04

LABEL author="ArhNex"

ENV TZ="Europe/Moscow"
RUN date

RUN apt-get -y update 

# for disable interactive mod apt-get
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends tzdata

RUN apt-get -y update 

# install some develop tools
RUN apt-get install -y gcc make nano check clang-format gcovr git valgrind htop lcov g++ 

# for gtest
RUN apt-get install -y libgtest-dev cmake
RUN mkdir -p $HOME/build
RUN cd $HOME/build
RUN cmake /usr/src/googletest/googletest
RUN make
# RUN cp -f lib/*.a /usr/lib/
RUN cd ..
RUN rm -rf build
RUN mkdir /usr/local/lib/googletest
RUN ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
RUN ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

#install zsh and oh-my-zsh
RUN apt-get install -y neofetch zsh curl

RUN curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh
RUN echo clear >> ~/.zshrc
RUN echo neofetch >> ~/.zshrc
RUN echo "alias sh='bash'" >> ~/.zshrc

RUN apt-get -y upgrade 
RUN mkdir /project

WORKDIR /project